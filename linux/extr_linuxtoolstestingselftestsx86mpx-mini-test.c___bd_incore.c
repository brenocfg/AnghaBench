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
 int /*<<< orphan*/  MPX_BOUNDS_DIR_SIZE_BYTES ; 
 int /*<<< orphan*/  bounds_dir_ptr ; 
 unsigned long nr_incore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned long __bd_incore(const char *func, int line)
{
	unsigned long ret = nr_incore(bounds_dir_ptr, MPX_BOUNDS_DIR_SIZE_BYTES);
	return ret;
}