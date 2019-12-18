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
struct nlm_lockowner {int dummy; } ;
struct file_lock {scalar_t__ fl_owner; } ;

/* Variables and functions */
 scalar_t__ nlmsvc_get_lockowner (struct nlm_lockowner*) ; 

__attribute__((used)) static void nlmsvc_locks_copy_lock(struct file_lock *new, struct file_lock *fl)
{
	struct nlm_lockowner *nlm_lo = (struct nlm_lockowner *)fl->fl_owner;
	new->fl_owner = nlmsvc_get_lockowner(nlm_lo);
}