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
struct TYPE_3__ {size_t** distances_prices; size_t** pos_slot_prices; size_t* align_prices; int /*<<< orphan*/  match_len_encoder; } ;
typedef  TYPE_1__ lzma_coder ;

/* Variables and functions */
 size_t const ALIGN_MASK ; 
 size_t const FULL_DISTANCES ; 
 size_t get_len_price (int /*<<< orphan*/ *,size_t const,size_t const) ; 
 size_t get_len_to_pos_state (size_t const) ; 
 size_t get_pos_slot_2 (size_t const) ; 

__attribute__((used)) static inline uint32_t
get_pos_len_price(const lzma_coder *const coder, const uint32_t pos,
		const uint32_t len, const uint32_t pos_state)
{
	const uint32_t len_to_pos_state = get_len_to_pos_state(len);
	uint32_t price;

	if (pos < FULL_DISTANCES) {
		price = coder->distances_prices[len_to_pos_state][pos];
	} else {
		const uint32_t pos_slot = get_pos_slot_2(pos);
		price = coder->pos_slot_prices[len_to_pos_state][pos_slot]
				+ coder->align_prices[pos & ALIGN_MASK];
	}

	price += get_len_price(&coder->match_len_encoder, len, pos_state);

	return price;
}