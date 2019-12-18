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
typedef  int /*<<< orphan*/  interval ;
struct TYPE_7__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_8__ {TYPE_1__ addr; } ;
struct TYPE_9__ {int keepalives_interval; int default_keepalives_interval; int /*<<< orphan*/  keepalives_idle; int /*<<< orphan*/  sock; TYPE_2__ laddr; } ;
typedef  TYPE_3__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ IS_AF_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  TCP_KEEPINTVL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ pq_getkeepalivesinterval (TYPE_3__*) ; 
 int pq_setkeepaliveswin32 (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
pq_setkeepalivesinterval(int interval, Port *port)
{
	if (port == NULL || IS_AF_UNIX(port->laddr.addr.ss_family))
		return STATUS_OK;

#if defined(TCP_KEEPINTVL) || defined(SIO_KEEPALIVE_VALS)
	if (interval == port->keepalives_interval)
		return STATUS_OK;

#ifndef WIN32
	if (port->default_keepalives_interval <= 0)
	{
		if (pq_getkeepalivesinterval(port) < 0)
		{
			if (interval == 0)
				return STATUS_OK;	/* default is set but unknown */
			else
				return STATUS_ERROR;
		}
	}

	if (interval == 0)
		interval = port->default_keepalives_interval;

	if (setsockopt(port->sock, IPPROTO_TCP, TCP_KEEPINTVL,
				   (char *) &interval, sizeof(interval)) < 0)
	{
		elog(LOG, "setsockopt(%s) failed: %m", "TCP_KEEPINTVL");
		return STATUS_ERROR;
	}

	port->keepalives_interval = interval;
#else							/* WIN32 */
	return pq_setkeepaliveswin32(port, port->keepalives_idle, interval);
#endif
#else
	if (interval != 0)
	{
		elog(LOG, "setsockopt(%s) not supported", "TCP_KEEPINTVL");
		return STATUS_ERROR;
	}
#endif

	return STATUS_OK;
}