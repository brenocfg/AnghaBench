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
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_query_list ; 
 int /*<<< orphan*/  tomoyo_query_wait ; 

__attribute__((used)) static __poll_t tomoyo_poll_query(struct file *file, poll_table *wait)
{
	if (!list_empty(&tomoyo_query_list))
		return EPOLLIN | EPOLLRDNORM;
	poll_wait(file, &tomoyo_query_wait, wait);
	if (!list_empty(&tomoyo_query_list))
		return EPOLLIN | EPOLLRDNORM;
	return 0;
}