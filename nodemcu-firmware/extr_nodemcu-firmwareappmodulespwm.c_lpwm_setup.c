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
 unsigned int NORMAL_PWM_DEPTH ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,void*) ; 
 void* platform_pwm_setup (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pwm ; 

__attribute__((used)) static int lpwm_setup( lua_State* L )
{
  s32 freq;	  // signed, to error check for negative values
  unsigned duty;
  unsigned id;

  id = luaL_checkinteger( L, 1 );
  if(id==0)
    return luaL_error( L, "no pwm for D0" );
  MOD_CHECK_ID( pwm, id );
  freq = luaL_checkinteger( L, 2 );
  if ( freq <= 0 )
    return luaL_error( L, "wrong arg range" );
  duty = luaL_checkinteger( L, 3 );
  if ( duty > NORMAL_PWM_DEPTH )
    // Negative values will turn out > 100, so will also fail.
    return luaL_error( L, "wrong arg range" );
  freq = platform_pwm_setup( id, (u32)freq, duty );
  if(freq==0)
    return luaL_error( L, "too many pwms." );
  lua_pushinteger( L, freq );
  return 1;
}