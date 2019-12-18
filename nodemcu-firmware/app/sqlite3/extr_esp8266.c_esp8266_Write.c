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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  scalar_t__ sint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ esp8266_file ;

/* Variables and functions */
 int SQLITE_IOERR_SEEK ; 
 int SQLITE_IOERR_WRITE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  VFS_SEEK_SET ; 
 int /*<<< orphan*/  dbg_printf (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ vfs_lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t vfs_write (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int esp8266_Write(sqlite3_file *id, const void *buffer, int amount, sqlite3_int64 offset)
{
	size_t nWrite;
	sint32_t ofst, iofst;
	esp8266_file *file = (esp8266_file*) id;

	iofst = (sint32_t)(offset & 0x7FFFFFFF);

	dbg_printf("esp8266_Write: 1w %s %d %d %lld[%ld] \n", file->name, file->fd, amount, offset, iofst);
	ofst = vfs_lseek(file->fd, iofst, VFS_SEEK_SET);
	if (ofst != iofst) {
		return SQLITE_IOERR_SEEK;
	}

	nWrite = vfs_write(file->fd, buffer, amount);
	if ( nWrite != amount ) {
		dbg_printf("esp8266_Write: 2w %s %u %d\n", file->name, nWrite, amount);
		return SQLITE_IOERR_WRITE;
	}

	dbg_printf("esp8266_Write: 3w %s OK\n", file->name);
	return SQLITE_OK;
}