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
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct netbuf {scalar_t__ len; struct sockaddr_in* buf; } ;

/* Variables and functions */
#define  AF_INET 128 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,int,int) ; 
 int /*<<< orphan*/ * inet_ntop (int,int /*<<< orphan*/ *,char*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

char *
__rpc_taddr2uaddr_af(int af, const struct netbuf *nbuf)
{
	char *ret;
	struct sockaddr_in *sin;
#ifdef AF_LOCAL
	struct sockaddr_un *sun;
#endif
	char namebuf[INET_ADDRSTRLEN];
#ifdef INET6
	struct sockaddr_in6 *sin6;
	char namebuf6[INET6_ADDRSTRLEN];
#endif
	u_int16_t port;

	if (nbuf->len <= 0)
		return NULL;

	switch (af) {
	case AF_INET:
#ifdef __REACTOS__ // CVE-2017-8779
		if (nbuf->len < sizeof(*sin)) {
			return NULL;
		}
#endif
		sin = nbuf->buf;
		if (inet_ntop(af, &sin->sin_addr, namebuf, sizeof namebuf)
		    == NULL)
			return NULL;
		port = ntohs(sin->sin_port);
		if (asprintf(&ret, "%s.%u.%u", namebuf, ((u_int32_t)port) >> 8,
		    port & 0xff) < 0)
			return NULL;
		break;
#ifdef INET6
	case AF_INET6:
#ifdef __REACTOS__ // CVE-2017-8779
		if (nbuf->len < sizeof(*sin6)) {
			return NULL;
		}
#endif
		sin6 = nbuf->buf;
		if (inet_ntop(af, &sin6->sin6_addr, namebuf6, sizeof namebuf6)
		    == NULL)
			return NULL;
		port = ntohs(sin6->sin6_port);
		if (asprintf(&ret, "%s.%u.%u", namebuf6, ((u_int32_t)port) >> 8,
		    port & 0xff) < 0)
			return NULL;
		break;
#endif
#ifdef AF_LOCAL
	case AF_LOCAL:
		sun = nbuf->buf;
		/*	if (asprintf(&ret, "%.*s", (int)(sun->sun_len -
		    offsetof(struct sockaddr_un, sun_path)),
		    sun->sun_path) < 0)*/
		if (asprintf(&ret, "%.*s", (int)(sizeof(*sun) -
						 offsetof(struct sockaddr_un, sun_path)),
			     sun->sun_path) < 0)

			return (NULL);
		break;
#endif
	default:
		return NULL;
	}

	return ret;
}