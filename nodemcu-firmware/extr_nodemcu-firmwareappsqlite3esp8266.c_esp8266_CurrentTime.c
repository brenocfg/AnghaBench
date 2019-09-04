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
 int /*<<< orphan*/  dbg_printf (char*,double) ; 

__attribute__((used)) static int esp8266_CurrentTime( sqlite3_vfs * vfs, double * result )
{
	// This is stubbed out until we have a working RTCTIME solution;
	// as it stood, this would always have returned the UNIX epoch.
	// time_t t = time(NULL);
	// *result = t / 86400.0 + 2440587.5;
	*result = 2440587.5;
	dbg_printf("esp8266_CurrentTime: %g\n", *result);
	return SQLITE_OK;
}