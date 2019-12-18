#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  idle ;
struct TYPE_7__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_8__ {TYPE_1__ addr; } ;
struct TYPE_9__ {int keepalives_idle; int default_keepalives_idle; int /*<<< orphan*/  keepalives_interval; int /*<<< orphan*/  sock; TYPE_2__ laddr; } ;
typedef  TYPE_3__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ IS_AF_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PG_TCP_KEEPALIVE_IDLE ; 
 int /*<<< orphan*/  PG_TCP_KEEPALIVE_IDLE_STR ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ pq_getkeepalivesidle (TYPE_3__*) ; 
 int pq_setkeepaliveswin32 (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
pq_setkeepalivesidle(int idle, Port *port)
{
	if (port == NULL || IS_AF_UNIX(port->laddr.addr.ss_family))
		return STATUS_OK;

/* check SIO_KEEPALIVE_VALS here, not just WIN32, as some toolchains lack it */
#if defined(PG_TCP_KEEPALIVE_IDLE) || defined(SIO_KEEPALIVE_VALS)
	if (idle == port->keepalives_idle)
		return STATUS_OK;

#ifndef WIN32
	if (port->default_keepalives_idle <= 0)
	{
		if (pq_getkeepalivesidle(port) < 0)
		{
			if (idle == 0)
				return STATUS_OK;	/* default is set but unknown */
			else
				return STATUS_ERROR;
		}
	}

	if (idle == 0)
		idle = port->default_keepalives_idle;

	if (setsockopt(port->sock, IPPROTO_TCP, PG_TCP_KEEPALIVE_IDLE,
				   (char *) &idle, sizeof(idle)) < 0)
	{
		elog(LOG, "setsockopt(%s) failed: %m", PG_TCP_KEEPALIVE_IDLE_STR);
		return STATUS_ERROR;
	}

	port->keepalives_idle = idle;
#else							/* WIN32 */
	return pq_setkeepaliveswin32(port, idle, port->keepalives_interval);
#endif
#else
	if (idle != 0)
	{
		elog(LOG, "setting the keepalive idle time is not supported");
		return STATUS_ERROR;
	}
#endif

	return STATUS_OK;
}