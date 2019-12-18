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
struct TYPE_6__ {char* data; } ;
typedef  int /*<<< orphan*/  PQconninfoOption ;
typedef  TYPE_1__ PQExpBufferData ;

/* Variables and functions */
 scalar_t__ PQExpBufferDataBroken (TYPE_1__) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/ * parse_connection_string (char const*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

PQconninfoOption *
PQconninfoParse(const char *conninfo, char **errmsg)
{
	PQExpBufferData errorBuf;
	PQconninfoOption *connOptions;

	if (errmsg)
		*errmsg = NULL;			/* default */
	initPQExpBuffer(&errorBuf);
	if (PQExpBufferDataBroken(errorBuf))
		return NULL;			/* out of memory already :-( */
	connOptions = parse_connection_string(conninfo, &errorBuf, false);
	if (connOptions == NULL && errmsg)
		*errmsg = errorBuf.data;
	else
		termPQExpBuffer(&errorBuf);
	return connOptions;
}