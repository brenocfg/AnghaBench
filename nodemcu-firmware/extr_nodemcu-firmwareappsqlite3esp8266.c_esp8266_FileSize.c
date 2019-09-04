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
typedef  long long sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ esp8266_file ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  dbg_printf (char*,int /*<<< orphan*/ ,long long,long long) ; 
 long long vfs_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp8266_FileSize(sqlite3_file *id, sqlite3_int64 *size)
{
	esp8266_file *file = (esp8266_file*) id;
	*size = 0LL | vfs_size( file->fd );
	dbg_printf("esp8266_FileSize: %s %u[%lld]\n", file->name, vfs_size(file->fd), *size);
	return SQLITE_OK;
}