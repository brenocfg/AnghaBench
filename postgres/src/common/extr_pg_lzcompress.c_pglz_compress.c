#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_4__ {scalar_t__ match_size_good; int min_input_size; int max_input_size; int match_size_drop; int min_comp_rate; int first_success_by; } ;
typedef  TYPE_1__ PGLZ_Strategy ;

/* Variables and functions */
 int INT_MAX ; 
 int PGLZ_MAX_MATCH ; 
 TYPE_1__* PGLZ_strategy_default ; 
 int /*<<< orphan*/  hist_entries ; 
 int /*<<< orphan*/  hist_start ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pglz_find_match (int /*<<< orphan*/ ,char const*,char const*,int*,int*,int,int,int) ; 
 int /*<<< orphan*/  pglz_hist_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char const*,char const*,int) ; 
 int /*<<< orphan*/  pglz_out_literal (unsigned char*,unsigned char,unsigned char,unsigned char*,char const) ; 
 int /*<<< orphan*/  pglz_out_tag (unsigned char*,unsigned char,unsigned char,unsigned char*,int,int) ; 

int32
pglz_compress(const char *source, int32 slen, char *dest,
			  const PGLZ_Strategy *strategy)
{
	unsigned char *bp = (unsigned char *) dest;
	unsigned char *bstart = bp;
	int			hist_next = 1;
	bool		hist_recycle = false;
	const char *dp = source;
	const char *dend = source + slen;
	unsigned char ctrl_dummy = 0;
	unsigned char *ctrlp = &ctrl_dummy;
	unsigned char ctrlb = 0;
	unsigned char ctrl = 0;
	bool		found_match = false;
	int32		match_len;
	int32		match_off;
	int32		good_match;
	int32		good_drop;
	int32		result_size;
	int32		result_max;
	int32		need_rate;
	int			hashsz;
	int			mask;

	/*
	 * Our fallback strategy is the default.
	 */
	if (strategy == NULL)
		strategy = PGLZ_strategy_default;

	/*
	 * If the strategy forbids compression (at all or if source chunk size out
	 * of range), fail.
	 */
	if (strategy->match_size_good <= 0 ||
		slen < strategy->min_input_size ||
		slen > strategy->max_input_size)
		return -1;

	/*
	 * Limit the match parameters to the supported range.
	 */
	good_match = strategy->match_size_good;
	if (good_match > PGLZ_MAX_MATCH)
		good_match = PGLZ_MAX_MATCH;
	else if (good_match < 17)
		good_match = 17;

	good_drop = strategy->match_size_drop;
	if (good_drop < 0)
		good_drop = 0;
	else if (good_drop > 100)
		good_drop = 100;

	need_rate = strategy->min_comp_rate;
	if (need_rate < 0)
		need_rate = 0;
	else if (need_rate > 99)
		need_rate = 99;

	/*
	 * Compute the maximum result size allowed by the strategy, namely the
	 * input size minus the minimum wanted compression rate.  This had better
	 * be <= slen, else we might overrun the provided output buffer.
	 */
	if (slen > (INT_MAX / 100))
	{
		/* Approximate to avoid overflow */
		result_max = (slen / 100) * (100 - need_rate);
	}
	else
		result_max = (slen * (100 - need_rate)) / 100;

	/*
	 * Experiments suggest that these hash sizes work pretty well. A large
	 * hash table minimizes collision, but has a higher startup cost. For a
	 * small input, the startup cost dominates. The table size must be a power
	 * of two.
	 */
	if (slen < 128)
		hashsz = 512;
	else if (slen < 256)
		hashsz = 1024;
	else if (slen < 512)
		hashsz = 2048;
	else if (slen < 1024)
		hashsz = 4096;
	else
		hashsz = 8192;
	mask = hashsz - 1;

	/*
	 * Initialize the history lists to empty.  We do not need to zero the
	 * hist_entries[] array; its entries are initialized as they are used.
	 */
	memset(hist_start, 0, hashsz * sizeof(int16));

	/*
	 * Compress the source directly into the output buffer.
	 */
	while (dp < dend)
	{
		/*
		 * If we already exceeded the maximum result size, fail.
		 *
		 * We check once per loop; since the loop body could emit as many as 4
		 * bytes (a control byte and 3-byte tag), PGLZ_MAX_OUTPUT() had better
		 * allow 4 slop bytes.
		 */
		if (bp - bstart >= result_max)
			return -1;

		/*
		 * If we've emitted more than first_success_by bytes without finding
		 * anything compressible at all, fail.  This lets us fall out
		 * reasonably quickly when looking at incompressible input (such as
		 * pre-compressed data).
		 */
		if (!found_match && bp - bstart >= strategy->first_success_by)
			return -1;

		/*
		 * Try to find a match in the history
		 */
		if (pglz_find_match(hist_start, dp, dend, &match_len,
							&match_off, good_match, good_drop, mask))
		{
			/*
			 * Create the tag and add history entries for all matched
			 * characters.
			 */
			pglz_out_tag(ctrlp, ctrlb, ctrl, bp, match_len, match_off);
			while (match_len--)
			{
				pglz_hist_add(hist_start, hist_entries,
							  hist_next, hist_recycle,
							  dp, dend, mask);
				dp++;			/* Do not do this ++ in the line above! */
				/* The macro would do it four times - Jan.  */
			}
			found_match = true;
		}
		else
		{
			/*
			 * No match found. Copy one literal byte.
			 */
			pglz_out_literal(ctrlp, ctrlb, ctrl, bp, *dp);
			pglz_hist_add(hist_start, hist_entries,
						  hist_next, hist_recycle,
						  dp, dend, mask);
			dp++;				/* Do not do this ++ in the line above! */
			/* The macro would do it four times - Jan.  */
		}
	}

	/*
	 * Write out the last control byte and check that we haven't overrun the
	 * output size allowed by the strategy.
	 */
	*ctrlp = ctrlb;
	result_size = bp - bstart;
	if (result_size >= result_max)
		return -1;

	/* success */
	return result_size;
}