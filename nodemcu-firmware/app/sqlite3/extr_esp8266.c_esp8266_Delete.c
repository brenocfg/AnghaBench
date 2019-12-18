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
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  scalar_t__ sint32_t ;

/* Variables and functions */
 int SQLITE_IOERR_DELETE ; 
 int SQLITE_OK ; 
 scalar_t__ VFS_RES_ERR ; 
 int /*<<< orphan*/  dbg_printf (char*,char const*) ; 
 scalar_t__ vfs_remove (char const*) ; 

__attribute__((used)) static int esp8266_Delete( sqlite3_vfs * vfs, const char * path, int syncDir )
{
	sint32_t rc = vfs_remove( path );
	if (rc == VFS_RES_ERR)
		return SQLITE_IOERR_DELETE;

	dbg_printf("esp8266_Delete: %s OK\n", path);
	return SQLITE_OK;
}