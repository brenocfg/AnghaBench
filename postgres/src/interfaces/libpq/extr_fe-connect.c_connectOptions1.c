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
struct TYPE_4__ {void* status; int /*<<< orphan*/  errorMessage; } ;
typedef  int /*<<< orphan*/  PQconninfoOption ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 void* CONNECTION_BAD ; 
 int /*<<< orphan*/  PQconninfoFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fillPGconn (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_connection_string (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
connectOptions1(PGconn *conn, const char *conninfo)
{
	PQconninfoOption *connOptions;

	/*
	 * Parse the conninfo string
	 */
	connOptions = parse_connection_string(conninfo, &conn->errorMessage, true);
	if (connOptions == NULL)
	{
		conn->status = CONNECTION_BAD;
		/* errorMessage is already set */
		return false;
	}

	/*
	 * Move option values into conn structure
	 */
	if (!fillPGconn(conn, connOptions))
	{
		conn->status = CONNECTION_BAD;
		PQconninfoFree(connOptions);
		return false;
	}

	/*
	 * Free the option info - all is in conn now
	 */
	PQconninfoFree(connOptions);

	return true;
}