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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ fd; } ;
typedef  TYPE_1__ file_fd_ud ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TUSERDATA ; 
 scalar_t__ file_fd_ref ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfs_close (scalar_t__) ; 

__attribute__((used)) static int file_close( lua_State* L )
{
  int need_pop = FALSE;
  file_fd_ud *ud;

  if (lua_type( L, 1 ) != LUA_TUSERDATA) {
    // fall back to last opened file
    if (file_fd_ref != LUA_NOREF) {
      lua_rawgeti( L, LUA_REGISTRYINDEX, file_fd_ref );
      // top of stack is now default file descriptor
      ud = (file_fd_ud *)luaL_checkudata(L, -1, "file.obj");
      lua_pop( L, 1 );
    } else {
      // no default file currently opened
      return 0;
    }
  } else {
    ud = (file_fd_ud *)luaL_checkudata(L, 1, "file.obj");
  }

  if(ud->fd){
      vfs_close(ud->fd);
      // mark as closed
      ud->fd = 0;
  }

  // unref default file descriptor
  luaL_unref( L, LUA_REGISTRYINDEX, file_fd_ref );
  file_fd_ref = LUA_NOREF;

  return 0;
}