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
typedef  int /*<<< orphan*/  lzma_range_encoder ;

/* Variables and functions */
 int /*<<< orphan*/  rc_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__ const) ; 

__attribute__((used)) static inline void
rc_bittree_reverse(lzma_range_encoder *rc, probability *probs,
		uint32_t bit_count, uint32_t symbol)
{
	uint32_t model_index = 1;

	do {
		const uint32_t bit = symbol & 1;
		symbol >>= 1;
		rc_bit(rc, &probs[model_index], bit);
		model_index = (model_index << 1) + bit;
	} while (--bit_count != 0);
}