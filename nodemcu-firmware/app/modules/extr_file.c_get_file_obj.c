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
struct TYPE_2__ {int fd; } ;
typedef  TYPE_1__ file_fd_ud ;

/* Variables and functions */
 scalar_t__ LUA_TUSERDATA ; 
 int file_fd ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int get_file_obj( lua_State *L, int *argpos )
{
  if (lua_type( L, 1 ) == LUA_TUSERDATA) {
    file_fd_ud *ud = (file_fd_ud *)luaL_checkudata(L, 1, "file.obj");
    *argpos = 2;
    return ud->fd;
  } else {
    *argpos = 1;
    return file_fd;
  }
}