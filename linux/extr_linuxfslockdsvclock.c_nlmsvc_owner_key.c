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
struct file_lock {scalar_t__ fl_pid; scalar_t__ fl_owner; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long
nlmsvc_owner_key(struct file_lock *fl)
{
	return (unsigned long)fl->fl_owner ^ (unsigned long)fl->fl_pid;
}