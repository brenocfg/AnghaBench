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
typedef  int /*<<< orphan*/  wait_queue_entry_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int autoremove_wake_function (int /*<<< orphan*/ *,unsigned int,int,void*) ; 
 int key_to_poll (void*) ; 

__attribute__((used)) static int receiver_wake_function(wait_queue_entry_t *wait, unsigned int mode, int sync,
				  void *key)
{
	/*
	 * Avoid a wakeup if event not interesting for us
	 */
	if (key && !(key_to_poll(key) & (EPOLLIN | EPOLLERR)))
		return 0;
	return autoremove_wake_function(wait, mode, sync, key);
}