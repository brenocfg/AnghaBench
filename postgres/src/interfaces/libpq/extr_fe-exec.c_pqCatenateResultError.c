#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* errMsg; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  TYPE_2__ PGresult ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  pqSetResultError (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

void
pqCatenateResultError(PGresult *res, const char *msg)
{
	PQExpBufferData errorBuf;

	if (!res || !msg)
		return;
	initPQExpBuffer(&errorBuf);
	if (res->errMsg)
		appendPQExpBufferStr(&errorBuf, res->errMsg);
	appendPQExpBufferStr(&errorBuf, msg);
	pqSetResultError(res, errorBuf.data);
	termPQExpBuffer(&errorBuf);
}