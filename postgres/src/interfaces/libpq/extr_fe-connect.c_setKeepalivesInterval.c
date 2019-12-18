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
typedef  int /*<<< orphan*/  interval ;
struct TYPE_4__ {int /*<<< orphan*/  errorMessage; int /*<<< orphan*/  sock; int /*<<< orphan*/ * keepalives_interval; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int PG_STRERROR_R_BUFLEN ; 
 int /*<<< orphan*/  SOCK_ERRNO ; 
 int /*<<< orphan*/  SOCK_STRERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TCP_KEEPINTVL ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  parse_int_param (int /*<<< orphan*/ *,int*,TYPE_1__*,char*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
setKeepalivesInterval(PGconn *conn)
{
	int			interval;

	if (conn->keepalives_interval == NULL)
		return 1;

	if (!parse_int_param(conn->keepalives_interval, &interval, conn,
						 "keepalives_interval"))
		return 0;
	if (interval < 0)
		interval = 0;

#ifdef TCP_KEEPINTVL
	if (setsockopt(conn->sock, IPPROTO_TCP, TCP_KEEPINTVL,
				   (char *) &interval, sizeof(interval)) < 0)
	{
		char		sebuf[PG_STRERROR_R_BUFLEN];

		appendPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("setsockopt(%s) failed: %s\n"),
						  "TCP_KEEPINTVL",
						  SOCK_STRERROR(SOCK_ERRNO, sebuf, sizeof(sebuf)));
		return 0;
	}
#endif

	return 1;
}