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
struct file_lock {int fl_flags; int fl_type; } ;

/* Variables and functions */
 int FL_DOWNGRADE_PENDING ; 
 int FL_UNLOCK_PENDING ; 
 int F_RDLCK ; 
 int F_UNLCK ; 

__attribute__((used)) static int target_leasetype(struct file_lock *fl)
{
	if (fl->fl_flags & FL_UNLOCK_PENDING)
		return F_UNLCK;
	if (fl->fl_flags & FL_DOWNGRADE_PENDING)
		return F_RDLCK;
	return fl->fl_type;
}