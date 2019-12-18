#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeout ;
struct TYPE_6__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_7__ {TYPE_1__ addr; } ;
struct TYPE_8__ {int tcp_user_timeout; int default_tcp_user_timeout; int /*<<< orphan*/  sock; TYPE_2__ laddr; } ;
typedef  TYPE_3__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ IS_AF_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  TCP_USER_TIMEOUT ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ pq_gettcpusertimeout (TYPE_3__*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int
pq_settcpusertimeout(int timeout, Port *port)
{
	if (port == NULL || IS_AF_UNIX(port->laddr.addr.ss_family))
		return STATUS_OK;

#ifdef TCP_USER_TIMEOUT
	if (timeout == port->tcp_user_timeout)
		return STATUS_OK;

	if (port->default_tcp_user_timeout <= 0)
	{
		if (pq_gettcpusertimeout(port) < 0)
		{
			if (timeout == 0)
				return STATUS_OK;	/* default is set but unknown */
			else
				return STATUS_ERROR;
		}
	}

	if (timeout == 0)
		timeout = port->default_tcp_user_timeout;

	if (setsockopt(port->sock, IPPROTO_TCP, TCP_USER_TIMEOUT,
				   (char *) &timeout, sizeof(timeout)) < 0)
	{
		elog(LOG, "setsockopt(%s) failed: %m", "TCP_USER_TIMEOUT");
		return STATUS_ERROR;
	}

	port->tcp_user_timeout = timeout;
#else
	if (timeout != 0)
	{
		elog(LOG, "setsockopt(%s) not supported", "TCP_USER_TIMEOUT");
		return STATUS_ERROR;
	}
#endif

	return STATUS_OK;
}