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
 int mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_mutex ; 

int rtnl_lock_killable(void)
{
	return mutex_lock_killable(&rtnl_mutex);
}