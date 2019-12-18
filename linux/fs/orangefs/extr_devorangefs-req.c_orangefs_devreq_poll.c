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
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  orangefs_request_list ; 
 int /*<<< orphan*/  orangefs_request_list_waitq ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t orangefs_devreq_poll(struct file *file,
				      struct poll_table_struct *poll_table)
{
	__poll_t poll_revent_mask = 0;

	poll_wait(file, &orangefs_request_list_waitq, poll_table);

	if (!list_empty(&orangefs_request_list))
		poll_revent_mask |= EPOLLIN;
	return poll_revent_mask;
}