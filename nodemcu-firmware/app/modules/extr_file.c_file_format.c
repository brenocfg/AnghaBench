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
 int /*<<< orphan*/  NODE_ERR (char*) ; 
 int /*<<< orphan*/  file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vfs_format () ; 

__attribute__((used)) static int file_format( lua_State* L )
{
  size_t len;
  file_close(L);
  if( !vfs_format() )
  {
    NODE_ERR( "\n*** ERROR ***: unable to format. FS might be compromised.\n" );
    NODE_ERR( "It is advised to re-flash the NodeMCU image.\n" );
    luaL_error(L, "Failed to format file system");
  }
  else{
    NODE_ERR( "format done.\n" );
  }
  return 0;
}