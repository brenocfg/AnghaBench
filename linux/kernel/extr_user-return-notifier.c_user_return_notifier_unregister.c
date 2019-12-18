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
 int /*<<< orphan*/  clear_tsk_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_notifier_list ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

void user_return_notifier_unregister(struct user_return_notifier *urn)
{
	hlist_del(&urn->link);
	if (hlist_empty(this_cpu_ptr(&return_notifier_list)))
		clear_tsk_thread_flag(current, TIF_USER_RETURN_NOTIFY);
}