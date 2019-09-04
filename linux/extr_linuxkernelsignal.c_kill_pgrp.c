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
struct pid {int dummy; } ;

/* Variables and functions */
 int __kill_pgrp_info (int,int /*<<< orphan*/ ,struct pid*) ; 
 int /*<<< orphan*/  __si_special (int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklist_lock ; 

int kill_pgrp(struct pid *pid, int sig, int priv)
{
	int ret;

	read_lock(&tasklist_lock);
	ret = __kill_pgrp_info(sig, __si_special(priv), pid);
	read_unlock(&tasklist_lock);

	return ret;
}