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
struct TYPE_2__ {int /*<<< orphan*/ * last_error_result; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
#define  PGRES_FATAL_ERROR 129 
#define  PGRES_NONFATAL_ERROR 128 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static void
ClearOrSaveResult(PGresult *result)
{
	if (result)
	{
		switch (PQresultStatus(result))
		{
			case PGRES_NONFATAL_ERROR:
			case PGRES_FATAL_ERROR:
				if (pset.last_error_result)
					PQclear(pset.last_error_result);
				pset.last_error_result = result;
				break;

			default:
				PQclear(result);
				break;
		}
	}
}