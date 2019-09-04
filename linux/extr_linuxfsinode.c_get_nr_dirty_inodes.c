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
 long get_nr_inodes () ; 
 long get_nr_inodes_unused () ; 

long get_nr_dirty_inodes(void)
{
	/* not actually dirty inodes, but a wild approximation */
	long nr_dirty = get_nr_inodes() - get_nr_inodes_unused();
	return nr_dirty > 0 ? nr_dirty : 0;
}