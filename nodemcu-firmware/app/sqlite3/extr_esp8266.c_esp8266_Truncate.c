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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int /*<<< orphan*/  esp8266_file ;

/* Variables and functions */
 int SQLITE_IOERR_TRUNCATE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  dbg_printf (char*) ; 

__attribute__((used)) static int esp8266_Truncate(sqlite3_file *id, sqlite3_int64 bytes)
{
	esp8266_file *file = (esp8266_file*) id;

	dbg_printf("esp8266_Truncate:\n");
	return 0 ? SQLITE_IOERR_TRUNCATE : SQLITE_OK;
}