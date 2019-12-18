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
typedef  int /*<<< orphan*/  PGresult ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int /*<<< orphan*/ * PQexecFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQexecStart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQsendQueryPrepared (int /*<<< orphan*/ *,char const*,int,char const* const*,int const*,int const*,int) ; 

PGresult *
PQexecPrepared(PGconn *conn,
			   const char *stmtName,
			   int nParams,
			   const char *const *paramValues,
			   const int *paramLengths,
			   const int *paramFormats,
			   int resultFormat)
{
	if (!PQexecStart(conn))
		return NULL;
	if (!PQsendQueryPrepared(conn, stmtName,
							 nParams, paramValues, paramLengths,
							 paramFormats, resultFormat))
		return NULL;
	return PQexecFinish(conn);
}