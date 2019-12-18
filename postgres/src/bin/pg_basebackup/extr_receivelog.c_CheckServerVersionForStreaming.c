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
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 char* PG_VERSION ; 
 int PG_VERSION_NUM ; 
 char* PQparameterStatus (int /*<<< orphan*/ *,char*) ; 
 int PQserverVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*,char*) ; 

bool
CheckServerVersionForStreaming(PGconn *conn)
{
	int			minServerMajor,
				maxServerMajor;
	int			serverMajor;

	/*
	 * The message format used in streaming replication changed in 9.3, so we
	 * cannot stream from older servers. And we don't support servers newer
	 * than the client; it might work, but we don't know, so err on the safe
	 * side.
	 */
	minServerMajor = 903;
	maxServerMajor = PG_VERSION_NUM / 100;
	serverMajor = PQserverVersion(conn) / 100;
	if (serverMajor < minServerMajor)
	{
		const char *serverver = PQparameterStatus(conn, "server_version");

		pg_log_error("incompatible server version %s; client does not support streaming from server versions older than %s",
					 serverver ? serverver : "'unknown'",
					 "9.3");
		return false;
	}
	else if (serverMajor > maxServerMajor)
	{
		const char *serverver = PQparameterStatus(conn, "server_version");

		pg_log_error("incompatible server version %s; client does not support streaming from server versions newer than %s",
					 serverver ? serverver : "'unknown'",
					 PG_VERSION);
		return false;
	}
	return true;
}