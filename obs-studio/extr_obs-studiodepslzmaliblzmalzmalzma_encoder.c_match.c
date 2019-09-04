#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {size_t const pos_special; size_t const pos_align; size_t* reps; int /*<<< orphan*/  match_price_count; int /*<<< orphan*/  align_price_count; int /*<<< orphan*/  rc; int /*<<< orphan*/ * pos_slot; int /*<<< orphan*/  fast_mode; int /*<<< orphan*/  match_len_encoder; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ lzma_coder ;

/* Variables and functions */
 size_t const ALIGN_BITS ; 
 size_t const ALIGN_MASK ; 
 size_t const END_POS_MODEL_INDEX ; 
 int /*<<< orphan*/  POS_SLOT_BITS ; 
 size_t const START_POS_MODEL_INDEX ; 
 size_t get_len_to_pos_state (size_t const) ; 
 size_t get_pos_slot (size_t const) ; 
 int /*<<< orphan*/  length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_bittree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  rc_bittree_reverse (int /*<<< orphan*/ *,size_t const,size_t const,size_t const) ; 
 int /*<<< orphan*/  rc_direct (int /*<<< orphan*/ *,size_t const,size_t const) ; 
 int /*<<< orphan*/  update_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
match(lzma_coder *coder, const uint32_t pos_state,
		const uint32_t distance, const uint32_t len)
{
	update_match(coder->state);

	length(&coder->rc, &coder->match_len_encoder, pos_state, len,
			coder->fast_mode);

	const uint32_t pos_slot = get_pos_slot(distance);
	const uint32_t len_to_pos_state = get_len_to_pos_state(len);
	rc_bittree(&coder->rc, coder->pos_slot[len_to_pos_state],
			POS_SLOT_BITS, pos_slot);

	if (pos_slot >= START_POS_MODEL_INDEX) {
		const uint32_t footer_bits = (pos_slot >> 1) - 1;
		const uint32_t base = (2 | (pos_slot & 1)) << footer_bits;
		const uint32_t pos_reduced = distance - base;

		if (pos_slot < END_POS_MODEL_INDEX) {
			// Careful here: base - pos_slot - 1 can be -1, but
			// rc_bittree_reverse starts at probs[1], not probs[0].
			rc_bittree_reverse(&coder->rc,
				coder->pos_special + base - pos_slot - 1,
				footer_bits, pos_reduced);
		} else {
			rc_direct(&coder->rc, pos_reduced >> ALIGN_BITS,
					footer_bits - ALIGN_BITS);
			rc_bittree_reverse(
					&coder->rc, coder->pos_align,
					ALIGN_BITS, pos_reduced & ALIGN_MASK);
			++coder->align_price_count;
		}
	}

	coder->reps[3] = coder->reps[2];
	coder->reps[2] = coder->reps[1];
	coder->reps[1] = coder->reps[0];
	coder->reps[0] = distance;
	++coder->match_price_count;
}