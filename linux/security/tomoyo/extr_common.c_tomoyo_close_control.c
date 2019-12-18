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
struct tomoyo_io_buffer {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ TOMOYO_QUERY ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_answer_wait ; 
 int /*<<< orphan*/  tomoyo_notify_gc (struct tomoyo_io_buffer*,int) ; 
 int /*<<< orphan*/  tomoyo_query_observers ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void tomoyo_close_control(struct tomoyo_io_buffer *head)
{
	/*
	 * If the file is /sys/kernel/security/tomoyo/query , decrement the
	 * observer counter.
	 */
	if (head->type == TOMOYO_QUERY &&
	    atomic_dec_and_test(&tomoyo_query_observers))
		wake_up_all(&tomoyo_answer_wait);
	tomoyo_notify_gc(head, false);
}