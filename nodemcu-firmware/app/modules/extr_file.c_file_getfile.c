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
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ file_fd_ud ;

/* Variables and functions */
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  LUAI_MAXINT32 ; 
 int /*<<< orphan*/  file_close (int /*<<< orphan*/ *) ; 
 int file_g_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_open (int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int file_getfile( lua_State* L )
{
  // Warning this code C calls other file_* routines to avoid duplication code.  These
  // use Lua stack addressing of arguments, so this does Lua stack maniplation to
  // align these
  int ret_cnt = 0;
  lua_settop(L ,1);
  // Stack [1] = FD
  file_open(L);
  // Stack [1] = filename; [2] = FD or nil
  if (!lua_isnil(L, -1)) {
    lua_remove(L, 1);  // dump filename, so [1] = FD
    file_fd_ud *ud = (file_fd_ud *)luaL_checkudata(L, 1, "file.obj");
    ret_cnt = file_g_read(L, LUAI_MAXINT32, EOF, ud->fd);
    // Stack [1] = FD; [2] = contents if ret_cnt = 1;
    file_close(L);     // leaves Stack unchanged if [1] = FD
    lua_remove(L, 1);  // Dump FD leaving contents as [1] / ToS
  }
  return ret_cnt;
}