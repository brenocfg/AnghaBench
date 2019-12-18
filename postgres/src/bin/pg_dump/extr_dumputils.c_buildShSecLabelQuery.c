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
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

void
buildShSecLabelQuery(PGconn *conn, const char *catalog_name, Oid objectId,
					 PQExpBuffer sql)
{
	appendPQExpBuffer(sql,
					  "SELECT provider, label FROM pg_catalog.pg_shseclabel "
					  "WHERE classoid = 'pg_catalog.%s'::pg_catalog.regclass "
					  "AND objoid = '%u'", catalog_name, objectId);
}