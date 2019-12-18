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
struct sockaddr_un {int dummy; } ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int getnameinfo (struct sockaddr const*,int,char*,int,char*,int,int) ; 
 int getnameinfo_unix (struct sockaddr_un const*,int,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

int
pg_getnameinfo_all(const struct sockaddr_storage *addr, int salen,
				   char *node, int nodelen,
				   char *service, int servicelen,
				   int flags)
{
	int			rc;

#ifdef HAVE_UNIX_SOCKETS
	if (addr && addr->ss_family == AF_UNIX)
		rc = getnameinfo_unix((const struct sockaddr_un *) addr, salen,
							  node, nodelen,
							  service, servicelen,
							  flags);
	else
#endif
		rc = getnameinfo((const struct sockaddr *) addr, salen,
						 node, nodelen,
						 service, servicelen,
						 flags);

	if (rc != 0)
	{
		if (node)
			strlcpy(node, "???", nodelen);
		if (service)
			strlcpy(service, "???", servicelen);
	}

	return rc;
}