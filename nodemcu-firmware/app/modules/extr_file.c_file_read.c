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
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 scalar_t__ EOF ; 
 unsigned int FILE_READ_CHUNK ; 
 int /*<<< orphan*/  GET_FILE_OBJ ; 
 scalar_t__ LUA_TNUMBER ; 
 int /*<<< orphan*/  argpos ; 
 int /*<<< orphan*/  fd ; 
 int file_g_read (int /*<<< orphan*/ *,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ luaL_checkinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int file_read( lua_State* L )
{
  unsigned need_len = FILE_READ_CHUNK;
  int16_t end_char = EOF;
  size_t el;

  GET_FILE_OBJ;

  if( lua_type( L, argpos ) == LUA_TNUMBER )
  {
    need_len = ( unsigned )luaL_checkinteger( L, argpos );
  }
  else if(lua_isstring(L, argpos))
  {
    const char *end = luaL_checklstring( L, argpos, &el );
    if(el!=1){
      return luaL_error( L, "wrong arg range" );
    }
    end_char = (int16_t)end[0];
  }

  return file_g_read(L, need_len, end_char, fd);
}