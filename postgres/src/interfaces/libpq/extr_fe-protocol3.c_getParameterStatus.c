#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__ workBuffer; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 scalar_t__ pqGets (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pqSaveParameterStatus (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static int
getParameterStatus(PGconn *conn)
{
	PQExpBufferData valueBuf;

	/* Get the parameter name */
	if (pqGets(&conn->workBuffer, conn))
		return EOF;
	/* Get the parameter value (could be large) */
	initPQExpBuffer(&valueBuf);
	if (pqGets(&valueBuf, conn))
	{
		termPQExpBuffer(&valueBuf);
		return EOF;
	}
	/* And save it */
	pqSaveParameterStatus(conn, conn->workBuffer.data, valueBuf.data);
	termPQExpBuffer(&valueBuf);
	return 0;
}