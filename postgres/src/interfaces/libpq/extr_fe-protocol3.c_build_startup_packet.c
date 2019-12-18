#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* pguser; char const* dbName; char const* replication; char const* pgoptions; char* appname; char* fbappname; char const* client_encoding_initial; scalar_t__ send_appname; int /*<<< orphan*/  pversion; } ;
struct TYPE_5__ {char* pgName; scalar_t__ envName; } ;
typedef  int /*<<< orphan*/  ProtocolVersion ;
typedef  TYPE_1__ PQEnvironmentOption ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STARTUP_OPTION (char*,char const*) ; 
 char* getenv (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_hton32 (int /*<<< orphan*/ ) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
build_startup_packet(const PGconn *conn, char *packet,
					 const PQEnvironmentOption *options)
{
	int			packet_len = 0;
	const PQEnvironmentOption *next_eo;
	const char *val;

	/* Protocol version comes first. */
	if (packet)
	{
		ProtocolVersion pv = pg_hton32(conn->pversion);

		memcpy(packet + packet_len, &pv, sizeof(ProtocolVersion));
	}
	packet_len += sizeof(ProtocolVersion);

	/* Add user name, database name, options */

#define ADD_STARTUP_OPTION(optname, optval) \
	do { \
		if (packet) \
			strcpy(packet + packet_len, optname); \
		packet_len += strlen(optname) + 1; \
		if (packet) \
			strcpy(packet + packet_len, optval); \
		packet_len += strlen(optval) + 1; \
	} while(0)

	if (conn->pguser && conn->pguser[0])
		ADD_STARTUP_OPTION("user", conn->pguser);
	if (conn->dbName && conn->dbName[0])
		ADD_STARTUP_OPTION("database", conn->dbName);
	if (conn->replication && conn->replication[0])
		ADD_STARTUP_OPTION("replication", conn->replication);
	if (conn->pgoptions && conn->pgoptions[0])
		ADD_STARTUP_OPTION("options", conn->pgoptions);
	if (conn->send_appname)
	{
		/* Use appname if present, otherwise use fallback */
		val = conn->appname ? conn->appname : conn->fbappname;
		if (val && val[0])
			ADD_STARTUP_OPTION("application_name", val);
	}

	if (conn->client_encoding_initial && conn->client_encoding_initial[0])
		ADD_STARTUP_OPTION("client_encoding", conn->client_encoding_initial);

	/* Add any environment-driven GUC settings needed */
	for (next_eo = options; next_eo->envName; next_eo++)
	{
		if ((val = getenv(next_eo->envName)) != NULL)
		{
			if (pg_strcasecmp(val, "default") != 0)
				ADD_STARTUP_OPTION(next_eo->pgName, val);
		}
	}

	/* Add trailing terminator */
	if (packet)
		packet[packet_len] = '\0';
	packet_len++;

	return packet_len;
}