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
 int /*<<< orphan*/  bounds_dir_ptr ; 
 int /*<<< orphan*/  check_clear (int /*<<< orphan*/ ,unsigned long) ; 

void check_clear_bd(void)
{
	check_clear(bounds_dir_ptr, 2UL << 30);
}