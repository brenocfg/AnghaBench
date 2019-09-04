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
struct TYPE_3__ {int prev_1_is_literal; scalar_t__ back_prev; } ;
typedef  TYPE_1__ lzma_optimal ;

/* Variables and functions */

__attribute__((used)) static inline void
make_short_rep(lzma_optimal *optimal)
{
	optimal->back_prev = 0;
	optimal->prev_1_is_literal = false;
}