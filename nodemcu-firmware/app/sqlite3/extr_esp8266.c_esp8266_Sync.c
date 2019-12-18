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
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ esp8266_file ;

/* Variables and functions */
 int SQLITE_IOERR_FSYNC ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  dbg_printf (char*,int) ; 
 int vfs_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp8266_Sync(sqlite3_file *id, int flags)
{
	esp8266_file *file = (esp8266_file*) id;

	int rc = vfs_flush( file->fd );
	dbg_printf("esp8266_Sync: %d\n", rc);

	return rc ? SQLITE_IOERR_FSYNC : SQLITE_OK;
}