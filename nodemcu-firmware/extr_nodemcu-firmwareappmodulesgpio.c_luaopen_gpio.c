#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_callback_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  lua_done_ref; int /*<<< orphan*/  done_taskid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_NOREF ; 
 TYPE_1__ serout ; 
 scalar_t__ seroutasync_done ; 
 int /*<<< orphan*/  task_get_id (int /*<<< orphan*/ ) ; 

int luaopen_gpio( lua_State *L ) {
#ifdef LUA_USE_MODULES_GPIO_PULSE
  gpio_pulse_init(L);
#endif
#ifdef GPIO_INTERRUPT_ENABLE
  int i;
  for(i=0;i<GPIO_PIN_NUM;i++){
    gpio_cb_ref[i] = LUA_NOREF;
  }
  platform_gpio_init(task_get_id(gpio_intr_callback_task));
#endif
  serout.done_taskid = task_get_id((task_callback_t) seroutasync_done);
  serout.lua_done_ref = LUA_NOREF;
  return 0;
}