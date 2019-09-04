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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ os_param_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  DATA ;

/* Variables and functions */
 int FALSE ; 
 int ROTARY_CHANNEL_COUNT ; 
 int TRUE ; 
 int /*<<< orphan*/ ** data ; 
 scalar_t__ lrotary_dequeue_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  task_post_medium (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasknumber ; 

__attribute__((used)) static void lrotary_task(os_param_t param, uint8_t prio)
{
  (void) param;
  (void) prio;

  uint8_t *task_queue_ptr = (uint8_t*) param;
  if (task_queue_ptr) {
    // Signal that new events may need another task post
    *task_queue_ptr = 0;
  }

  int id;
  bool need_to_post = FALSE;
  lua_State *L = lua_getstate();

  for (id = 0; id < ROTARY_CHANNEL_COUNT; id++) {
    DATA *d = data[id];
    if (d) {
      if (lrotary_dequeue_single(L, d)) {
	need_to_post = TRUE;
      }
    }
  }

  if (need_to_post) {
    // If there is pending stuff, queue another task
    task_post_medium(tasknumber, 0);
  }
}