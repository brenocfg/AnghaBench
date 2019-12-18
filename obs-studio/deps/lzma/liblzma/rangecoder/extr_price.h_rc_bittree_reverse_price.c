#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  probability ;

/* Variables and functions */
 scalar_t__ rc_bit_price (int /*<<< orphan*/  const,scalar_t__ const) ; 

__attribute__((used)) static inline uint32_t
rc_bittree_reverse_price(const probability *const probs,
		uint32_t bit_levels, uint32_t symbol)
{
	uint32_t price = 0;
	uint32_t model_index = 1;

	do {
		const uint32_t bit = symbol & 1;
		symbol >>= 1;
		price += rc_bit_price(probs[model_index], bit);
		model_index = (model_index << 1) + bit;
	} while (--bit_levels != 0);

	return price;
}