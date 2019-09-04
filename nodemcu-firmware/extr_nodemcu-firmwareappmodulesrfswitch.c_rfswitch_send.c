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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send (unsigned int,unsigned int,unsigned int,unsigned int,unsigned long,unsigned long) ; 

__attribute__((used)) static int rfswitch_send( lua_State *L )
{
  unsigned int protocol_id = luaL_checkinteger( L, 1 );
  unsigned int pulse_length = luaL_checkinteger( L, 2 );
  unsigned int repeat = luaL_checkinteger( L, 3 );
  unsigned int pin = luaL_checkinteger( L, 4 );
  unsigned long value = luaL_checkinteger( L, 5 );
  unsigned long length = luaL_checkinteger( L, 6 );
  send(protocol_id, pulse_length, repeat, pin, value, length);
  return 0;
}