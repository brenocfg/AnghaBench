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
struct vfs_stat {int dummy; } ;
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  scalar_t__ sint32_t ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ VFS_RES_ERR ; 
 int /*<<< orphan*/  dbg_printf (char*,int) ; 
 scalar_t__ vfs_stat (char const*,struct vfs_stat*) ; 

__attribute__((used)) static int esp8266_Access( sqlite3_vfs * vfs, const char * path, int flags, int * result )
{
	struct vfs_stat st;
	sint32_t rc = vfs_stat( path, &st );
	*result = ( rc != VFS_RES_ERR );

	dbg_printf("esp8266_Access: %d\n", *result);
	return SQLITE_OK;
}