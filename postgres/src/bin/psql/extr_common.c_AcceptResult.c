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
struct TYPE_2__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  CheckConnection () ; 
#define  PGRES_BAD_RESPONSE 135 
#define  PGRES_COMMAND_OK 134 
#define  PGRES_COPY_IN 133 
#define  PGRES_COPY_OUT 132 
#define  PGRES_EMPTY_QUERY 131 
#define  PGRES_FATAL_ERROR 130 
#define  PGRES_NONFATAL_ERROR 129 
#define  PGRES_TUPLES_OK 128 
 char* PQerrorMessage (int /*<<< orphan*/ ) ; 
 int PQresultStatus (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int) ; 
 int /*<<< orphan*/  pg_log_info (char*,char const*) ; 
 TYPE_1__ pset ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static bool
AcceptResult(const PGresult *result)
{
	bool		OK;

	if (!result)
		OK = false;
	else
		switch (PQresultStatus(result))
		{
			case PGRES_COMMAND_OK:
			case PGRES_TUPLES_OK:
			case PGRES_EMPTY_QUERY:
			case PGRES_COPY_IN:
			case PGRES_COPY_OUT:
				/* Fine, do nothing */
				OK = true;
				break;

			case PGRES_BAD_RESPONSE:
			case PGRES_NONFATAL_ERROR:
			case PGRES_FATAL_ERROR:
				OK = false;
				break;

			default:
				OK = false;
				pg_log_error("unexpected PQresultStatus: %d",
							 PQresultStatus(result));
				break;
		}

	if (!OK)
	{
		const char *error = PQerrorMessage(pset.db);

		if (strlen(error))
			pg_log_info("%s", error);

		CheckConnection();
	}

	return OK;
}