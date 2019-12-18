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
struct file_lock {int fl_flags; } ;

/* Variables and functions */
 int FL_DOWNGRADE_PENDING ; 
 int FL_UNLOCK_PENDING ; 

__attribute__((used)) static bool lease_breaking(struct file_lock *fl)
{
	return fl->fl_flags & (FL_UNLOCK_PENDING | FL_DOWNGRADE_PENDING);
}