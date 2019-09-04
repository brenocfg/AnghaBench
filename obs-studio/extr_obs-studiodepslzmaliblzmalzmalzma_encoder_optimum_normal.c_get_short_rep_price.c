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
typedef  size_t lzma_lzma_state ;
struct TYPE_3__ {int /*<<< orphan*/ ** is_rep0_long; int /*<<< orphan*/ * is_rep0; } ;
typedef  TYPE_1__ lzma_coder ;

/* Variables and functions */
 size_t rc_bit_0_price (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
get_short_rep_price(const lzma_coder *const coder,
		const lzma_lzma_state state, const uint32_t pos_state)
{
	return rc_bit_0_price(coder->is_rep0[state])
		+ rc_bit_0_price(coder->is_rep0_long[state][pos_state]);
}