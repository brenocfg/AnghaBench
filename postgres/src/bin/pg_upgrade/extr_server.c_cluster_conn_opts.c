#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  user; } ;
struct TYPE_12__ {int /*<<< orphan*/  port; int /*<<< orphan*/  sockdir; } ;
struct TYPE_11__ {char* data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  TYPE_2__ ClusterInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  appendShellString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* createPQExpBuffer () ; 
 TYPE_4__ os_info ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_1__*) ; 

char *
cluster_conn_opts(ClusterInfo *cluster)
{
	static PQExpBuffer buf;

	if (buf == NULL)
		buf = createPQExpBuffer();
	else
		resetPQExpBuffer(buf);

	if (cluster->sockdir)
	{
		appendPQExpBufferStr(buf, "--host ");
		appendShellString(buf, cluster->sockdir);
		appendPQExpBufferChar(buf, ' ');
	}
	appendPQExpBuffer(buf, "--port %d --username ", cluster->port);
	appendShellString(buf, os_info.user);

	return buf->data;
}