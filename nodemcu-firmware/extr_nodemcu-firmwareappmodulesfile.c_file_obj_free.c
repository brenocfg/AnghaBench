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
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vfs_close (scalar_t__) ; 

__attribute__((used)) static int file_obj_free( lua_State *L )
{
  file_fd_ud *ud = (file_fd_ud *)luaL_checkudata(L, 1, "file.obj");
  if (ud->fd) {
    // close file if it's still open
    vfs_close(ud->fd);
    ud->fd = 0;
  }

  return 0;
}