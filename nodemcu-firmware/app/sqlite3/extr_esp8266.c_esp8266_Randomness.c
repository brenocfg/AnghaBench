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

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  dbg_printf (char*,int) ; 
 int os_get_random (char*,int) ; 

__attribute__((used)) static int esp8266_Randomness( sqlite3_vfs * vfs, int len, char * buffer )
{
	int rc = os_get_random(buffer, len);
	dbg_printf("esp8266_Randomness: %d\n", rc);
	return SQLITE_OK;
}