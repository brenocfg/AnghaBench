#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  instr_time ;
struct TYPE_6__ {char* data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 double INSTR_TIME_GET_DOUBLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SUBTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char*,double) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * doConnect () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const,...) ; 
 int /*<<< orphan*/  initCreateFKeys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initCreatePKeys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initCreateTables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initDropTables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initGenerateDataClientSide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initGenerateDataServerSide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  initVacuum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static void
runInitSteps(const char *initialize_steps)
{
	PQExpBufferData stats;
	PGconn	   *con;
	const char *step;
	double		run_time = 0.0;
	bool		first = true;

	initPQExpBuffer(&stats);

	if ((con = doConnect()) == NULL)
		exit(1);

	for (step = initialize_steps; *step != '\0'; step++)
	{
		instr_time	start;
		char	   *op = NULL;

		INSTR_TIME_SET_CURRENT(start);

		switch (*step)
		{
			case 'd':
				op = "drop tables";
				initDropTables(con);
				break;
			case 't':
				op = "create tables";
				initCreateTables(con);
				break;
			case 'g':
				op = "client-side generate";
				initGenerateDataClientSide(con);
				break;
			case 'G':
				op = "server-side generate";
				initGenerateDataServerSide(con);
				break;
			case 'v':
				op = "vacuum";
				initVacuum(con);
				break;
			case 'p':
				op = "primary keys";
				initCreatePKeys(con);
				break;
			case 'f':
				op = "foreign keys";
				initCreateFKeys(con);
				break;
			case ' ':
				break;			/* ignore */
			default:
				fprintf(stderr, "unrecognized initialization step \"%c\"\n",
						*step);
				PQfinish(con);
				exit(1);
		}

		if (op != NULL)
		{
			instr_time	diff;
			double		elapsed_sec;

			INSTR_TIME_SET_CURRENT(diff);
			INSTR_TIME_SUBTRACT(diff, start);
			elapsed_sec = INSTR_TIME_GET_DOUBLE(diff);

			if (!first)
				appendPQExpBufferStr(&stats, ", ");
			else
				first = false;

			appendPQExpBuffer(&stats, "%s %.2f s", op, elapsed_sec);

			run_time += elapsed_sec;
		}
	}

	fprintf(stderr, "done in %.2f s (%s).\n", run_time, stats.data);
	PQfinish(con);
	termPQExpBuffer(&stats);
}