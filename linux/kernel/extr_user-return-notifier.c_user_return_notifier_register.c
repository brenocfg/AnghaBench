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
struct user_return_notifier {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_USER_RETURN_NOTIFY ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_notifier_list ; 
 int /*<<< orphan*/  set_tsk_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

void user_return_notifier_register(struct user_return_notifier *urn)
{
	set_tsk_thread_flag(current, TIF_USER_RETURN_NOTIFY);
	hlist_add_head(&urn->link, this_cpu_ptr(&return_notifier_list));
}