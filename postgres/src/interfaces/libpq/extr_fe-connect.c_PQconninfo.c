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
struct TYPE_3__ {scalar_t__ connofs; scalar_t__ keyword; } ;
typedef  TYPE_1__ internalPQconninfoOption ;
typedef  int /*<<< orphan*/  PQconninfoOption ;
typedef  int /*<<< orphan*/  PQExpBufferData ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ PQExpBufferDataBroken (int /*<<< orphan*/ ) ; 
 TYPE_1__* PQconninfoOptions ; 
 int /*<<< orphan*/ * conninfo_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conninfo_storeval (int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  initPQExpBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  termPQExpBuffer (int /*<<< orphan*/ *) ; 

PQconninfoOption *
PQconninfo(PGconn *conn)
{
	PQExpBufferData errorBuf;
	PQconninfoOption *connOptions;

	if (conn == NULL)
		return NULL;

	/* We don't actually report any errors here, but callees want a buffer */
	initPQExpBuffer(&errorBuf);
	if (PQExpBufferDataBroken(errorBuf))
		return NULL;			/* out of memory already :-( */

	connOptions = conninfo_init(&errorBuf);

	if (connOptions != NULL)
	{
		const internalPQconninfoOption *option;

		for (option = PQconninfoOptions; option->keyword; option++)
		{
			char	  **connmember;

			if (option->connofs < 0)
				continue;

			connmember = (char **) ((char *) conn + option->connofs);

			if (*connmember)
				conninfo_storeval(connOptions, option->keyword, *connmember,
								  &errorBuf, true, false);
		}
	}

	termPQExpBuffer(&errorBuf);

	return connOptions;
}