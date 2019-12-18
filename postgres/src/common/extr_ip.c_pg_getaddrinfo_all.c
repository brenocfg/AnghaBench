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
struct addrinfo {scalar_t__ ai_family; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int getaddrinfo (char const*,char const*,struct addrinfo const*,struct addrinfo**) ; 
 int getaddrinfo_unix (char const*,struct addrinfo const*,struct addrinfo**) ; 

int
pg_getaddrinfo_all(const char *hostname, const char *servname,
				   const struct addrinfo *hintp, struct addrinfo **result)
{
	int			rc;

	/* not all versions of getaddrinfo() zero *result on failure */
	*result = NULL;

#ifdef HAVE_UNIX_SOCKETS
	if (hintp->ai_family == AF_UNIX)
		return getaddrinfo_unix(servname, hintp, result);
#endif

	/* NULL has special meaning to getaddrinfo(). */
	rc = getaddrinfo((!hostname || hostname[0] == '\0') ? NULL : hostname,
					 servname, hintp, result);

	return rc;
}