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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tomoyo_log_count ; 
 int /*<<< orphan*/  tomoyo_log_wait ; 

__poll_t tomoyo_poll_log(struct file *file, poll_table *wait)
{
	if (tomoyo_log_count)
		return EPOLLIN | EPOLLRDNORM;
	poll_wait(file, &tomoyo_log_wait, wait);
	if (tomoyo_log_count)
		return EPOLLIN | EPOLLRDNORM;
	return 0;
}