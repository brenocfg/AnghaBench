#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * streamConn; } ;
typedef  TYPE_1__ WalReceiverConn ;
struct TYPE_13__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {char* val; int /*<<< orphan*/ * keyword; int /*<<< orphan*/  dispchar; } ;
typedef  TYPE_2__ PQconninfoOption ;
typedef  TYPE_3__ PQExpBufferData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PQExpBufferDataBroken (TYPE_3__) ; 
 TYPE_2__* PQconninfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQconninfoFree (TYPE_2__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_3__*,char*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_3__*) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_3__*) ; 

__attribute__((used)) static char *
libpqrcv_get_conninfo(WalReceiverConn *conn)
{
	PQconninfoOption *conn_opts;
	PQconninfoOption *conn_opt;
	PQExpBufferData buf;
	char	   *retval;

	Assert(conn->streamConn != NULL);

	initPQExpBuffer(&buf);
	conn_opts = PQconninfo(conn->streamConn);

	if (conn_opts == NULL)
		ereport(ERROR,
				(errmsg("could not parse connection string: %s",
						_("out of memory"))));

	/* build a clean connection string from pieces */
	for (conn_opt = conn_opts; conn_opt->keyword != NULL; conn_opt++)
	{
		bool		obfuscate;

		/* Skip debug and empty options */
		if (strchr(conn_opt->dispchar, 'D') ||
			conn_opt->val == NULL ||
			conn_opt->val[0] == '\0')
			continue;

		/* Obfuscate security-sensitive options */
		obfuscate = strchr(conn_opt->dispchar, '*') != NULL;

		appendPQExpBuffer(&buf, "%s%s=%s",
						  buf.len == 0 ? "" : " ",
						  conn_opt->keyword,
						  obfuscate ? "********" : conn_opt->val);
	}

	PQconninfoFree(conn_opts);

	retval = PQExpBufferDataBroken(buf) ? NULL : pstrdup(buf.data);
	termPQExpBuffer(&buf);
	return retval;
}