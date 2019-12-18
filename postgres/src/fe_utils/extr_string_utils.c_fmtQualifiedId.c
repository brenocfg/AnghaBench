#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char const*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 char const* fmtId (char const*) ; 
 TYPE_1__* getLocalPQExpBuffer () ; 

const char *
fmtQualifiedId(const char *schema, const char *id)
{
	PQExpBuffer id_return;
	PQExpBuffer lcl_pqexp = createPQExpBuffer();

	/* Some callers might fail to provide a schema name */
	if (schema && *schema)
	{
		appendPQExpBuffer(lcl_pqexp, "%s.", fmtId(schema));
	}
	appendPQExpBufferStr(lcl_pqexp, fmtId(id));

	id_return = getLocalPQExpBuffer();

	appendPQExpBufferStr(id_return, lcl_pqexp->data);
	destroyPQExpBuffer(lcl_pqexp);

	return id_return->data;
}