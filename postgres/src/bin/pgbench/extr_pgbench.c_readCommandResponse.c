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
struct TYPE_4__ {int id; int use_file; int command; int /*<<< orphan*/  con; int /*<<< orphan*/  ecnt; } ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_1__ CState ;

/* Variables and functions */
#define  PGRES_COMMAND_OK 130 
#define  PGRES_EMPTY_QUERY 129 
#define  PGRES_TUPLES_OK 128 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ ) ; 
 char* PQfname (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int PQnfields (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  pg_free (char*) ; 
 char* psprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  putVariable (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool
readCommandResponse(CState *st, char *varprefix)
{
	PGresult   *res;
	PGresult   *next_res;
	int			qrynum = 0;

	res = PQgetResult(st->con);

	while (res != NULL)
	{
		bool		is_last;

		/* peek at the next result to know whether the current is last */
		next_res = PQgetResult(st->con);
		is_last = (next_res == NULL);

		switch (PQresultStatus(res))
		{
			case PGRES_COMMAND_OK:	/* non-SELECT commands */
			case PGRES_EMPTY_QUERY: /* may be used for testing no-op overhead */
				if (is_last && varprefix != NULL)
				{
					fprintf(stderr,
							"client %d script %d command %d query %d: expected one row, got %d\n",
							st->id, st->use_file, st->command, qrynum, 0);
					goto error;
				}
				break;

			case PGRES_TUPLES_OK:
				if (is_last && varprefix != NULL)
				{
					if (PQntuples(res) != 1)
					{
						fprintf(stderr,
								"client %d script %d command %d query %d: expected one row, got %d\n",
								st->id, st->use_file, st->command, qrynum, PQntuples(res));
						goto error;
					}

					/* store results into variables */
					for (int fld = 0; fld < PQnfields(res); fld++)
					{
						char	   *varname = PQfname(res, fld);

						/* allocate varname only if necessary, freed below */
						if (*varprefix != '\0')
							varname = psprintf("%s%s", varprefix, varname);

						/* store result as a string */
						if (!putVariable(st, "gset", varname,
										 PQgetvalue(res, 0, fld)))
						{
							/* internal error */
							fprintf(stderr,
									"client %d script %d command %d query %d: error storing into variable %s\n",
									st->id, st->use_file, st->command, qrynum,
									varname);
							goto error;
						}

						if (*varprefix != '\0')
							pg_free(varname);
					}
				}
				/* otherwise the result is simply thrown away by PQclear below */
				break;

			default:
				/* anything else is unexpected */
				fprintf(stderr,
						"client %d script %d aborted in command %d query %d: %s",
						st->id, st->use_file, st->command, qrynum,
						PQerrorMessage(st->con));
				goto error;
		}

		PQclear(res);
		qrynum++;
		res = next_res;
	}

	if (qrynum == 0)
	{
		fprintf(stderr, "client %d command %d: no results\n", st->id, st->command);
		st->ecnt++;
		return false;
	}

	return true;

error:
	st->ecnt++;
	PQclear(res);
	PQclear(next_res);
	do
	{
		res = PQgetResult(st->con);
		PQclear(res);
	} while (res);

	return false;
}