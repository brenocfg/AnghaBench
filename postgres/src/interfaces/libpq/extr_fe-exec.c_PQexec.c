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
 int /*<<< orphan*/  PQsendQuery (int /*<<< orphan*/ *,char const*) ; 

PGresult *
PQexec(PGconn *conn, const char *query)
{
	if (!PQexecStart(conn))
		return NULL;
	if (!PQsendQuery(conn, query))
		return NULL;
	return PQexecFinish(conn);
}