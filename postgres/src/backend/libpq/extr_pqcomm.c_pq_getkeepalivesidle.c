#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_6__ {TYPE_1__ addr; } ;
struct TYPE_7__ {scalar_t__ keepalives_idle; int default_keepalives_idle; int /*<<< orphan*/  sock; TYPE_2__ laddr; } ;
typedef  TYPE_3__ Port ;
typedef  int ACCEPT_TYPE_ARG3 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ IS_AF_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PG_TCP_KEEPALIVE_IDLE ; 
 int /*<<< orphan*/  PG_TCP_KEEPALIVE_IDLE_STR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

int
pq_getkeepalivesidle(Port *port)
{
#if defined(PG_TCP_KEEPALIVE_IDLE) || defined(SIO_KEEPALIVE_VALS)
	if (port == NULL || IS_AF_UNIX(port->laddr.addr.ss_family))
		return 0;

	if (port->keepalives_idle != 0)
		return port->keepalives_idle;

	if (port->default_keepalives_idle == 0)
	{
#ifndef WIN32
		ACCEPT_TYPE_ARG3 size = sizeof(port->default_keepalives_idle);

		if (getsockopt(port->sock, IPPROTO_TCP, PG_TCP_KEEPALIVE_IDLE,
					   (char *) &port->default_keepalives_idle,
					   &size) < 0)
		{
			elog(LOG, "getsockopt(%s) failed: %m", PG_TCP_KEEPALIVE_IDLE_STR);
			port->default_keepalives_idle = -1; /* don't know */
		}
#else							/* WIN32 */
		/* We can't get the defaults on Windows, so return "don't know" */
		port->default_keepalives_idle = -1;
#endif							/* WIN32 */
	}

	return port->default_keepalives_idle;
#else
	return 0;
#endif
}