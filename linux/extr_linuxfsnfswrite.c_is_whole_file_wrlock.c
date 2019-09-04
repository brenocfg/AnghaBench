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
struct file_lock {scalar_t__ fl_start; scalar_t__ fl_end; scalar_t__ fl_type; } ;

/* Variables and functions */
 scalar_t__ F_WRLCK ; 
 scalar_t__ OFFSET_MAX ; 

__attribute__((used)) static bool
is_whole_file_wrlock(struct file_lock *fl)
{
	return fl->fl_start == 0 && fl->fl_end == OFFSET_MAX &&
			fl->fl_type == F_WRLCK;
}