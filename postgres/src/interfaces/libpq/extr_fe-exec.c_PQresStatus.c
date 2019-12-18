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
typedef  size_t ExecStatusType ;

/* Variables and functions */
 char* libpq_gettext (char*) ; 
 char** pgresStatus ; 

char *
PQresStatus(ExecStatusType status)
{
	if ((unsigned int) status >= sizeof pgresStatus / sizeof pgresStatus[0])
		return libpq_gettext("invalid ExecStatusType code");
	return pgresStatus[status];
}