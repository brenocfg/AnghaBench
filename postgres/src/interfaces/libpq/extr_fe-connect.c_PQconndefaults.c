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
typedef  int /*<<< orphan*/  PQconninfoOption ;
typedef  int /*<<< orphan*/  PQExpBufferData ;

/* Variables and functions */
 scalar_t__ PQExpBufferDataBroken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQconninfoFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conninfo_add_defaults (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * conninfo_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initPQExpBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  termPQExpBuffer (int /*<<< orphan*/ *) ; 

PQconninfoOption *
PQconndefaults(void)
{
	PQExpBufferData errorBuf;
	PQconninfoOption *connOptions;

	/* We don't actually report any errors here, but callees want a buffer */
	initPQExpBuffer(&errorBuf);
	if (PQExpBufferDataBroken(errorBuf))
		return NULL;			/* out of memory already :-( */

	connOptions = conninfo_init(&errorBuf);
	if (connOptions != NULL)
	{
		/* pass NULL errorBuf to ignore errors */
		if (!conninfo_add_defaults(connOptions, NULL))
		{
			PQconninfoFree(connOptions);
			connOptions = NULL;
		}
	}

	termPQExpBuffer(&errorBuf);
	return connOptions;
}