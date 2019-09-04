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
typedef  int /*<<< orphan*/  u32 ;
typedef  void* s32 ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_CHECK_ID (int /*<<< orphan*/ ,unsigned int) ; 
 void* NORMAL_PWM_DEPTH ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,void*) ; 
 void* platform_pwm_set_duty (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm ; 

__attribute__((used)) static int lpwm_setduty( lua_State* L )
{
  unsigned id;
  s32 duty;  // signed to error-check for negative values

  id = luaL_checkinteger( L, 1 );
  MOD_CHECK_ID( pwm, id );
  duty = luaL_checkinteger( L, 2 );
  if ( duty > NORMAL_PWM_DEPTH )
    return luaL_error( L, "wrong arg range" );
  duty = platform_pwm_set_duty( id, (u32)duty );
  lua_pushinteger( L, duty );
  return 1;
}