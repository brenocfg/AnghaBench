#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file_lock {scalar_t__ fl_owner; TYPE_1__* fl_lmops; } ;
struct TYPE_2__ {unsigned long (* lm_owner_key ) (struct file_lock*) ;} ;

/* Variables and functions */
 unsigned long stub1 (struct file_lock*) ; 

__attribute__((used)) static unsigned long
posix_owner_key(struct file_lock *fl)
{
	if (fl->fl_lmops && fl->fl_lmops->lm_owner_key)
		return fl->fl_lmops->lm_owner_key(fl);
	return (unsigned long)fl->fl_owner;
}