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
struct sparsebit {scalar_t__ num_set; scalar_t__ root; } ;

/* Variables and functions */

bool sparsebit_all_set(struct sparsebit *s)
{
	/*
	 * If any nodes there must be at least one bit set.  Only case
	 * where a bit is set and total num set is 0, is when all bits
	 * are set.
	 */
	return s->root && s->num_set == 0;
}