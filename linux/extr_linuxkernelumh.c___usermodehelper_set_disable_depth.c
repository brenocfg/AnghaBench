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
typedef  enum umh_disable_depth { ____Placeholder_umh_disable_depth } umh_disable_depth ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umhelper_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int usermodehelper_disabled ; 
 int /*<<< orphan*/  usermodehelper_disabled_waitq ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void __usermodehelper_set_disable_depth(enum umh_disable_depth depth)
{
	down_write(&umhelper_sem);
	usermodehelper_disabled = depth;
	wake_up(&usermodehelper_disabled_waitq);
	up_write(&umhelper_sem);
}