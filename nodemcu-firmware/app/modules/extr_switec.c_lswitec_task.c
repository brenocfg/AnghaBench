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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  os_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  lswitec_dequeue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getstate () ; 

__attribute__((used)) static void lswitec_task(os_param_t param, uint8_t prio)
{
  (void) param;
  (void) prio;

  lswitec_dequeue(lua_getstate());
}