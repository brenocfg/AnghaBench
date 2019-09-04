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
struct tnum {int mask; int value; } ;

/* Variables and functions */

bool tnum_in(struct tnum a, struct tnum b)
{
	if (b.mask & ~a.mask)
		return false;
	b.value &= ~a.mask;
	return a.value == b.value;
}