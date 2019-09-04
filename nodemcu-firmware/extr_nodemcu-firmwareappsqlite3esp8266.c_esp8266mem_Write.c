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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  cache; } ;
typedef  TYPE_1__ esp8266_file ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  dbg_printf (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  filecache_push (int /*<<< orphan*/ ,scalar_t__,int,void const*) ; 

__attribute__((used)) static int esp8266mem_Write(sqlite3_file *id, const void *buffer, int amount, sqlite3_int64 offset)
{
	sint32_t ofst;
	esp8266_file *file = (esp8266_file*) id;

	ofst = (sint32_t)(offset & 0x7FFFFFFF);

	filecache_push (file->cache, ofst, amount, buffer);

	dbg_printf("esp8266mem_Write: %s [%ld] [%d] OK\n", file->name, ofst, amount);
	return SQLITE_OK;
}