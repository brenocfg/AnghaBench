#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char const* user; } ;
struct TYPE_11__ {char const* sockdir; int /*<<< orphan*/  port; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ PQExpBufferData ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_2__ ClusterInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * PQconnectdb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendConnStrVal (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_1__*) ; 
 TYPE_4__ os_info ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_1__*) ; 

__attribute__((used)) static PGconn *
get_db_conn(ClusterInfo *cluster, const char *db_name)
{
	PQExpBufferData conn_opts;
	PGconn	   *conn;

	/* Build connection string with proper quoting */
	initPQExpBuffer(&conn_opts);
	appendPQExpBufferStr(&conn_opts, "dbname=");
	appendConnStrVal(&conn_opts, db_name);
	appendPQExpBufferStr(&conn_opts, " user=");
	appendConnStrVal(&conn_opts, os_info.user);
	appendPQExpBuffer(&conn_opts, " port=%d", cluster->port);
	if (cluster->sockdir)
	{
		appendPQExpBufferStr(&conn_opts, " host=");
		appendConnStrVal(&conn_opts, cluster->sockdir);
	}

	conn = PQconnectdb(conn_opts.data);
	termPQExpBuffer(&conn_opts);
	return conn;
}