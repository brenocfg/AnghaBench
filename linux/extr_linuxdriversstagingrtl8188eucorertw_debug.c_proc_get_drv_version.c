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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 char* DRIVERVERSION ; 
 scalar_t__ snprintf (char*,int,char*,char*) ; 

int proc_get_drv_version(char *page, char **start,
			  off_t offset, int count,
			  int *eof, void *data)
{
	int len = 0;

	len += snprintf(page + len, count - len, "%s\n", DRIVERVERSION);

	*eof = 1;
	return len;
}