#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * errMsg; } ;
typedef  TYPE_1__ PGresult ;

/* Variables and functions */
 int /*<<< orphan*/ * pqResultStrdup (TYPE_1__*,char const*) ; 

void
pqSetResultError(PGresult *res, const char *msg)
{
	if (!res)
		return;
	if (msg && *msg)
		res->errMsg = pqResultStrdup(res, msg);
	else
		res->errMsg = NULL;
}