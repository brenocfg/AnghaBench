#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ id; TYPE_2__* hooks; } ;

/* Variables and functions */
 int HOOK_CONFIG_COUNT ; 
 TYPE_2__* current_hooks ; 
 TYPE_1__* safety_hook_registry ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int safety_set_mode(uint16_t mode, int16_t param) {
  for (int i = 0; i < HOOK_CONFIG_COUNT; i++) {
    if (safety_hook_registry[i].id == mode) {
      current_hooks = safety_hook_registry[i].hooks;
      if (current_hooks->init) current_hooks->init(param);
      return 0;
    }
  }
  return -1;
}