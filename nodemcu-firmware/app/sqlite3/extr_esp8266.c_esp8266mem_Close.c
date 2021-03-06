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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  cache; } ;
typedef  TYPE_1__ esp8266_file ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  dbg_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filecache_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esp8266mem_Close(sqlite3_file *id)
{
	esp8266_file *file = (esp8266_file*) id;

	filecache_free(file->cache);
	sqlite3_free (file->cache);

	dbg_printf("esp8266mem_Close: %s OK\n", file->name);
	return SQLITE_OK;
}