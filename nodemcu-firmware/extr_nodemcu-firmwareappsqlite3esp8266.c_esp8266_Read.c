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
 int SQLITE_IOERR_READ ; 
 int SQLITE_IOERR_SHORT_READ ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  VFS_SEEK_SET ; 
 int /*<<< orphan*/  dbg_printf (char*,scalar_t__,...) ; 
 scalar_t__ vfs_lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t vfs_read (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int esp8266_Read(sqlite3_file *id, void *buffer, int amount, sqlite3_int64 offset)
{
	size_t nRead;
	sint32_t ofst, iofst;
	esp8266_file *file = (esp8266_file*) id;

	iofst = (sint32_t)(offset & 0x7FFFFFFF);

	dbg_printf("esp8266_Read: 1r %s %d %d %lld[%ld] \n", file->name, file->fd, amount, offset, iofst);
	ofst = vfs_lseek(file->fd, iofst, VFS_SEEK_SET);
	if (ofst != iofst) {
	        dbg_printf("esp8266_Read: 2r %ld != %ld FAIL\n", ofst, iofst);
		return SQLITE_IOERR_SHORT_READ /* SQLITE_IOERR_SEEK */;
	}

	nRead = vfs_read(file->fd, buffer, amount);
	if ( nRead == amount ) {
	        dbg_printf("esp8266_Read: 3r %s %u %d OK\n", file->name, nRead, amount);
		return SQLITE_OK;
	} else if ( nRead >= 0 ) {
	        dbg_printf("esp8266_Read: 3r %s %u %d FAIL\n", file->name, nRead, amount);
		return SQLITE_IOERR_SHORT_READ;
	}

	dbg_printf("esp8266_Read: 4r %s FAIL\n", file->name);
	return SQLITE_IOERR_READ;
}