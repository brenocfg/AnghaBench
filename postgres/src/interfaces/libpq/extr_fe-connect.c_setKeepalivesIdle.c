#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sebuf ;
typedef  int /*<<< orphan*/  idle ;
struct TYPE_4__ {int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  sock; int /*<<< orphan*/ * keepalives_idle; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int PG_STRERROR_R_BUFLEN ; 
 int /*<<< orphan*/  PG_TCP_KEEPALIVE_IDLE ; 
 int /*<<< orphan*/  PG_TCP_KEEPALIVE_IDLE_STR ; 
 int /*<<< orphan*/  SOCK_ERRNO ; 
 int /*<<< orphan*/  SOCK_STRERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  parse_int_param (int /*<<< orphan*/ *,int*,TYPE_1__*,char*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
setKeepalivesIdle(PGconn *conn)
{
	int			idle;

	if (conn->keepalives_idle == NULL)
		return 1;

	if (!parse_int_param(conn->keepalives_idle, &idle, conn,
						 "keepalives_idle"))
		return 0;
	if (idle < 0)
		idle = 0;

#ifdef PG_TCP_KEEPALIVE_IDLE
	if (setsockopt(conn->sock, IPPROTO_TCP, PG_TCP_KEEPALIVE_IDLE,
				   (char *) &idle, sizeof(idle)) < 0)
	{
		char		sebuf[PG_STRERROR_R_BUFLEN];

		appendPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("setsockopt(%s) failed: %s\n"),
						  PG_TCP_KEEPALIVE_IDLE_STR,
						  SOCK_STRERROR(SOCK_ERRNO, sebuf, sizeof(sebuf)));
		return 0;
	}
#endif

	return 1;
}