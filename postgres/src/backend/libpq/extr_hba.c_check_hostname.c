#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct addrinfo {TYPE_1__* ai_addr; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  remote_hostname ;
struct TYPE_9__ {scalar_t__ ss_family; } ;
struct TYPE_7__ {TYPE_4__ addr; int /*<<< orphan*/  salen; } ;
struct TYPE_8__ {int remote_hostname_resolv; int remote_hostname_errcode; TYPE_2__ raddr; int /*<<< orphan*/  remote_hostname; } ;
typedef  TYPE_3__ hbaPort ;
struct TYPE_6__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NAMEREQD ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int /*<<< orphan*/  hostname_match (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4eq (struct sockaddr_in*,struct sockaddr_in*) ; 
 scalar_t__ ipv6eq (struct sockaddr_in6*,struct sockaddr_in6*) ; 
 int pg_getnameinfo_all (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (char*) ; 

__attribute__((used)) static bool
check_hostname(hbaPort *port, const char *hostname)
{
	struct addrinfo *gai_result,
			   *gai;
	int			ret;
	bool		found;

	/* Quick out if remote host name already known bad */
	if (port->remote_hostname_resolv < 0)
		return false;

	/* Lookup remote host name if not already done */
	if (!port->remote_hostname)
	{
		char		remote_hostname[NI_MAXHOST];

		ret = pg_getnameinfo_all(&port->raddr.addr, port->raddr.salen,
								 remote_hostname, sizeof(remote_hostname),
								 NULL, 0,
								 NI_NAMEREQD);
		if (ret != 0)
		{
			/* remember failure; don't complain in the postmaster log yet */
			port->remote_hostname_resolv = -2;
			port->remote_hostname_errcode = ret;
			return false;
		}

		port->remote_hostname = pstrdup(remote_hostname);
	}

	/* Now see if remote host name matches this pg_hba line */
	if (!hostname_match(hostname, port->remote_hostname))
		return false;

	/* If we already verified the forward lookup, we're done */
	if (port->remote_hostname_resolv == +1)
		return true;

	/* Lookup IP from host name and check against original IP */
	ret = getaddrinfo(port->remote_hostname, NULL, NULL, &gai_result);
	if (ret != 0)
	{
		/* remember failure; don't complain in the postmaster log yet */
		port->remote_hostname_resolv = -2;
		port->remote_hostname_errcode = ret;
		return false;
	}

	found = false;
	for (gai = gai_result; gai; gai = gai->ai_next)
	{
		if (gai->ai_addr->sa_family == port->raddr.addr.ss_family)
		{
			if (gai->ai_addr->sa_family == AF_INET)
			{
				if (ipv4eq((struct sockaddr_in *) gai->ai_addr,
						   (struct sockaddr_in *) &port->raddr.addr))
				{
					found = true;
					break;
				}
			}
#ifdef HAVE_IPV6
			else if (gai->ai_addr->sa_family == AF_INET6)
			{
				if (ipv6eq((struct sockaddr_in6 *) gai->ai_addr,
						   (struct sockaddr_in6 *) &port->raddr.addr))
				{
					found = true;
					break;
				}
			}
#endif
		}
	}

	if (gai_result)
		freeaddrinfo(gai_result);

	if (!found)
		elog(DEBUG2, "pg_hba.conf host name \"%s\" rejected because address resolution did not return a match with IP address of client",
			 hostname);

	port->remote_hostname_resolv = found ? +1 : -1;

	return found;
}