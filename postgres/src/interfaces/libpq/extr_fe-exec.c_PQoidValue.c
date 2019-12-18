#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* cmdStatus; } ;
typedef  TYPE_1__ PGresult ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 unsigned long strtoul (char*,char**,int) ; 

Oid
PQoidValue(const PGresult *res)
{
	char	   *endptr = NULL;
	unsigned long result;

	if (!res ||
		strncmp(res->cmdStatus, "INSERT ", 7) != 0 ||
		res->cmdStatus[7] < '0' ||
		res->cmdStatus[7] > '9')
		return InvalidOid;

	result = strtoul(res->cmdStatus + 7, &endptr, 10);

	if (!endptr || (*endptr != ' ' && *endptr != '\0'))
		return InvalidOid;
	else
		return (Oid) result;
}