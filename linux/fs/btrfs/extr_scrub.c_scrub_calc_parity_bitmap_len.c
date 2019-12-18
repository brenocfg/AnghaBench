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

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int scrub_calc_parity_bitmap_len(int nsectors)
{
	return DIV_ROUND_UP(nsectors, BITS_PER_LONG) * sizeof(long);
}