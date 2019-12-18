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
struct TYPE_7__ {scalar_t__ tcp_user_timeout; int default_tcp_user_timeout; int /*<<< orphan*/  sock; TYPE_2__ laddr; } ;
typedef  TYPE_3__ Port ;
typedef  int ACCEPT_TYPE_ARG3 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ IS_AF_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  TCP_USER_TIMEOUT ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

int
pq_gettcpusertimeout(Port *port)
{
#ifdef TCP_USER_TIMEOUT
	if (port == NULL || IS_AF_UNIX(port->laddr.addr.ss_family))
		return 0;

	if (port->tcp_user_timeout != 0)
		return port->tcp_user_timeout;

	if (port->default_tcp_user_timeout == 0)
	{
		ACCEPT_TYPE_ARG3 size = sizeof(port->default_tcp_user_timeout);

		if (getsockopt(port->sock, IPPROTO_TCP, TCP_USER_TIMEOUT,
					   (char *) &port->default_tcp_user_timeout,
					   &size) < 0)
		{
			elog(LOG, "getsockopt(%s) failed: %m", "TCP_USER_TIMEOUT");
			port->default_tcp_user_timeout = -1;	/* don't know */
		}
	}

	return port->default_tcp_user_timeout;
#else
	return 0;
#endif
}