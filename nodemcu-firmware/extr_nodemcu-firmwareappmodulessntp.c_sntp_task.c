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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  SNTP_DOLOOKUPS_ID ; 
 int /*<<< orphan*/  SNTP_HANDLE_RESULT_ID ; 
 int /*<<< orphan*/  handle_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  sntp_dolookups (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sntp_handle_result (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sntp_task(os_param_t param, uint8_t prio)
{
  (void) param;
  (void) prio;

  lua_State *L = lua_getstate();

  if (param == SNTP_HANDLE_RESULT_ID) {
    sntp_handle_result(L);
  } else if (param == SNTP_DOLOOKUPS_ID) {
    sntp_dolookups(L);
  } else {
    handle_error(L, param, NULL);
  }
}