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
typedef  size_t uint8 ;
typedef  int /*<<< orphan*/  os_event_t ;

/* Variables and functions */
 size_t TASK_PRIORITY_HIGH ; 
 scalar_t__ os_malloc (int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int system_os_task (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ ** task_Q ; 
 int /*<<< orphan*/  task_dispatch ; 

bool task_init_handler(uint8 priority, uint8 qlen) {
  if (priority <= TASK_PRIORITY_HIGH && task_Q[priority] == NULL) {
    task_Q[priority] = (os_event_t *) os_malloc( sizeof(os_event_t)*qlen );
    os_memset (task_Q[priority], 0, sizeof(os_event_t)*qlen);
    if (task_Q[priority]) {
      return system_os_task( task_dispatch, priority, task_Q[priority], qlen );
    }
  }
  return false;
}