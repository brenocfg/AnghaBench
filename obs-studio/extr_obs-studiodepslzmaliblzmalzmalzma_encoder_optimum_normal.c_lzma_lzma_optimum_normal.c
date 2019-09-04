#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  reps ;
struct TYPE_16__ {scalar_t__ read_ahead; int /*<<< orphan*/  nice_len; } ;
typedef  TYPE_2__ lzma_mf ;
struct TYPE_17__ {size_t opts_end_index; size_t opts_current_index; int match_price_count; scalar_t__ align_price_count; int /*<<< orphan*/  longest_match_length; int /*<<< orphan*/  matches; int /*<<< orphan*/  matches_count; int /*<<< orphan*/  reps; TYPE_1__* opts; } ;
typedef  TYPE_3__ lzma_coder ;
struct TYPE_15__ {int pos_prev; int back_prev; } ;

/* Variables and functions */
 scalar_t__ ALIGN_TABLE_SIZE ; 
 int OPTS ; 
 int REP_DISTANCES ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  backward (TYPE_3__*,int*,int*,int) ; 
 int /*<<< orphan*/  fill_align_prices (TYPE_3__*) ; 
 int /*<<< orphan*/  fill_distances_prices (TYPE_3__*) ; 
 int helper1 (TYPE_3__*,TYPE_2__*,int*,int*,int) ; 
 int helper2 (TYPE_3__*,int*,scalar_t__,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mf_avail (TYPE_2__*) ; 
 int /*<<< orphan*/  mf_find (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mf_ptr (TYPE_2__*) ; 
 int /*<<< orphan*/  my_min (scalar_t__,int) ; 

extern void
lzma_lzma_optimum_normal(lzma_coder *restrict coder, lzma_mf *restrict mf,
		uint32_t *restrict back_res, uint32_t *restrict len_res,
		uint32_t position)
{
	// If we have symbols pending, return the next pending symbol.
	if (coder->opts_end_index != coder->opts_current_index) {
		assert(mf->read_ahead > 0);
		*len_res = coder->opts[coder->opts_current_index].pos_prev
				- coder->opts_current_index;
		*back_res = coder->opts[coder->opts_current_index].back_prev;
		coder->opts_current_index = coder->opts[
				coder->opts_current_index].pos_prev;
		return;
	}

	// Update the price tables. In LZMA SDK <= 4.60 (and possibly later)
	// this was done in both initialization function and in the main loop.
	// In liblzma they were moved into this single place.
	if (mf->read_ahead == 0) {
		if (coder->match_price_count >= (1 << 7))
			fill_distances_prices(coder);

		if (coder->align_price_count >= ALIGN_TABLE_SIZE)
			fill_align_prices(coder);
	}

	// TODO: This needs quite a bit of cleaning still. But splitting
	// the original function into two pieces makes it at least a little
	// more readable, since those two parts don't share many variables.

	uint32_t len_end = helper1(coder, mf, back_res, len_res, position);
	if (len_end == UINT32_MAX)
		return;

	uint32_t reps[REP_DISTANCES];
	memcpy(reps, coder->reps, sizeof(reps));

	uint32_t cur;
	for (cur = 1; cur < len_end; ++cur) {
		assert(cur < OPTS);

		coder->longest_match_length = mf_find(
				mf, &coder->matches_count, coder->matches);

		if (coder->longest_match_length >= mf->nice_len)
			break;

		len_end = helper2(coder, reps, mf_ptr(mf) - 1, len_end,
				position + cur, cur, mf->nice_len,
				my_min(mf_avail(mf) + 1, OPTS - 1 - cur));
	}

	backward(coder, len_res, back_res, cur);
	return;
}