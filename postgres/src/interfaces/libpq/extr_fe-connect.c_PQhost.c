#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t whichhost; TYPE_1__* connhost; } ;
struct TYPE_4__ {char* host; char* hostaddr; } ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */

char *
PQhost(const PGconn *conn)
{
	if (!conn)
		return NULL;

	if (conn->connhost != NULL)
	{
		/*
		 * Return the verbatim host value provided by user, or hostaddr in its
		 * lack.
		 */
		if (conn->connhost[conn->whichhost].host != NULL &&
			conn->connhost[conn->whichhost].host[0] != '\0')
			return conn->connhost[conn->whichhost].host;
		else if (conn->connhost[conn->whichhost].hostaddr != NULL &&
				 conn->connhost[conn->whichhost].hostaddr[0] != '\0')
			return conn->connhost[conn->whichhost].hostaddr;
	}

	return "";
}