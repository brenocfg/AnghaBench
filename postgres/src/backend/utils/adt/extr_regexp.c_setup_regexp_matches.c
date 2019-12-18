#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_15__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
struct TYPE_16__ {int npatterns; int* match_locs; int conv_bufsiz; int /*<<< orphan*/ * conv_buf; TYPE_1__* wide_str; int /*<<< orphan*/  nmatches; int /*<<< orphan*/ * orig_str; } ;
typedef  TYPE_2__ regexp_matches_ctx ;
struct TYPE_17__ {int re_nsub; } ;
typedef  TYPE_3__ regex_t ;
typedef  TYPE_1__ pg_wchar ;
struct TYPE_18__ {scalar_t__ glob; int /*<<< orphan*/  cflags; } ;
typedef  TYPE_5__ pg_re_flags ;
typedef  int int64 ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int MaxAllocSize ; 
 TYPE_3__* RE_compile_and_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RE_wchar_execute (TYPE_3__*,TYPE_1__*,int,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 void* palloc (int) ; 
 TYPE_2__* palloc0 (int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int pg_database_encoding_max_length () ; 
 int pg_mb2wchar_with_len (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ repalloc (int*,int) ; 

__attribute__((used)) static regexp_matches_ctx *
setup_regexp_matches(text *orig_str, text *pattern, pg_re_flags *re_flags,
					 Oid collation,
					 bool use_subpatterns,
					 bool ignore_degenerate,
					 bool fetching_unmatched)
{
	regexp_matches_ctx *matchctx = palloc0(sizeof(regexp_matches_ctx));
	int			eml = pg_database_encoding_max_length();
	int			orig_len;
	pg_wchar   *wide_str;
	int			wide_len;
	regex_t    *cpattern;
	regmatch_t *pmatch;
	int			pmatch_len;
	int			array_len;
	int			array_idx;
	int			prev_match_end;
	int			prev_valid_match_end;
	int			start_search;
	int			maxlen = 0;		/* largest fetch length in characters */

	/* save original string --- we'll extract result substrings from it */
	matchctx->orig_str = orig_str;

	/* convert string to pg_wchar form for matching */
	orig_len = VARSIZE_ANY_EXHDR(orig_str);
	wide_str = (pg_wchar *) palloc(sizeof(pg_wchar) * (orig_len + 1));
	wide_len = pg_mb2wchar_with_len(VARDATA_ANY(orig_str), wide_str, orig_len);

	/* set up the compiled pattern */
	cpattern = RE_compile_and_cache(pattern, re_flags->cflags, collation);

	/* do we want to remember subpatterns? */
	if (use_subpatterns && cpattern->re_nsub > 0)
	{
		matchctx->npatterns = cpattern->re_nsub;
		pmatch_len = cpattern->re_nsub + 1;
	}
	else
	{
		use_subpatterns = false;
		matchctx->npatterns = 1;
		pmatch_len = 1;
	}

	/* temporary output space for RE package */
	pmatch = palloc(sizeof(regmatch_t) * pmatch_len);

	/*
	 * the real output space (grown dynamically if needed)
	 *
	 * use values 2^n-1, not 2^n, so that we hit the limit at 2^28-1 rather
	 * than at 2^27
	 */
	array_len = re_flags->glob ? 255 : 31;
	matchctx->match_locs = (int *) palloc(sizeof(int) * array_len);
	array_idx = 0;

	/* search for the pattern, perhaps repeatedly */
	prev_match_end = 0;
	prev_valid_match_end = 0;
	start_search = 0;
	while (RE_wchar_execute(cpattern, wide_str, wide_len, start_search,
							pmatch_len, pmatch))
	{
		/*
		 * If requested, ignore degenerate matches, which are zero-length
		 * matches occurring at the start or end of a string or just after a
		 * previous match.
		 */
		if (!ignore_degenerate ||
			(pmatch[0].rm_so < wide_len &&
			 pmatch[0].rm_eo > prev_match_end))
		{
			/* enlarge output space if needed */
			while (array_idx + matchctx->npatterns * 2 + 1 > array_len)
			{
				array_len += array_len + 1; /* 2^n-1 => 2^(n+1)-1 */
				if (array_len > MaxAllocSize / sizeof(int))
					ereport(ERROR,
							(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
							 errmsg("too many regular expression matches")));
				matchctx->match_locs = (int *) repalloc(matchctx->match_locs,
														sizeof(int) * array_len);
			}

			/* save this match's locations */
			if (use_subpatterns)
			{
				int			i;

				for (i = 1; i <= matchctx->npatterns; i++)
				{
					int			so = pmatch[i].rm_so;
					int			eo = pmatch[i].rm_eo;

					matchctx->match_locs[array_idx++] = so;
					matchctx->match_locs[array_idx++] = eo;
					if (so >= 0 && eo >= 0 && (eo - so) > maxlen)
						maxlen = (eo - so);
				}
			}
			else
			{
				int			so = pmatch[0].rm_so;
				int			eo = pmatch[0].rm_eo;

				matchctx->match_locs[array_idx++] = so;
				matchctx->match_locs[array_idx++] = eo;
				if (so >= 0 && eo >= 0 && (eo - so) > maxlen)
					maxlen = (eo - so);
			}
			matchctx->nmatches++;

			/*
			 * check length of unmatched portion between end of previous valid
			 * (nondegenerate, or degenerate but not ignored) match and start
			 * of current one
			 */
			if (fetching_unmatched &&
				pmatch[0].rm_so >= 0 &&
				(pmatch[0].rm_so - prev_valid_match_end) > maxlen)
				maxlen = (pmatch[0].rm_so - prev_valid_match_end);
			prev_valid_match_end = pmatch[0].rm_eo;
		}
		prev_match_end = pmatch[0].rm_eo;

		/* if not glob, stop after one match */
		if (!re_flags->glob)
			break;

		/*
		 * Advance search position.  Normally we start the next search at the
		 * end of the previous match; but if the match was of zero length, we
		 * have to advance by one character, or we'd just find the same match
		 * again.
		 */
		start_search = prev_match_end;
		if (pmatch[0].rm_so == pmatch[0].rm_eo)
			start_search++;
		if (start_search > wide_len)
			break;
	}

	/*
	 * check length of unmatched portion between end of last match and end of
	 * input string
	 */
	if (fetching_unmatched &&
		(wide_len - prev_valid_match_end) > maxlen)
		maxlen = (wide_len - prev_valid_match_end);

	/*
	 * Keep a note of the end position of the string for the benefit of
	 * splitting code.
	 */
	matchctx->match_locs[array_idx] = wide_len;

	if (eml > 1)
	{
		int64		maxsiz = eml * (int64) maxlen;
		int			conv_bufsiz;

		/*
		 * Make the conversion buffer large enough for any substring of
		 * interest.
		 *
		 * Worst case: assume we need the maximum size (maxlen*eml), but take
		 * advantage of the fact that the original string length in bytes is
		 * an upper bound on the byte length of any fetched substring (and we
		 * know that len+1 is safe to allocate because the varlena header is
		 * longer than 1 byte).
		 */
		if (maxsiz > orig_len)
			conv_bufsiz = orig_len + 1;
		else
			conv_bufsiz = maxsiz + 1;	/* safe since maxsiz < 2^30 */

		matchctx->conv_buf = palloc(conv_bufsiz);
		matchctx->conv_bufsiz = conv_bufsiz;
		matchctx->wide_str = wide_str;
	}
	else
	{
		/* No need to keep the wide string if we're in a single-byte charset. */
		pfree(wide_str);
		matchctx->wide_str = NULL;
		matchctx->conv_buf = NULL;
		matchctx->conv_bufsiz = 0;
	}

	/* Clean up temp storage */
	pfree(pmatch);

	return matchctx;
}