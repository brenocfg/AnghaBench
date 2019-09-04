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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  portbuf ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  addrbuf ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int RPCBIND_MAXUADDRLEN ; 
 int RPCBIND_MAXUADDRPLEN ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_ntop4 (struct sockaddr const*,char*,int) ; 
 int /*<<< orphan*/  rpc_ntop6_noscopeid (struct sockaddr const*,char*,int) ; 
 int snprintf (char*,int,char*,unsigned short,unsigned short) ; 
 int strlcat (char*,char*,int) ; 

char *rpc_sockaddr2uaddr(const struct sockaddr *sap, gfp_t gfp_flags)
{
	char portbuf[RPCBIND_MAXUADDRPLEN];
	char addrbuf[RPCBIND_MAXUADDRLEN];
	unsigned short port;

	switch (sap->sa_family) {
	case AF_INET:
		if (rpc_ntop4(sap, addrbuf, sizeof(addrbuf)) == 0)
			return NULL;
		port = ntohs(((struct sockaddr_in *)sap)->sin_port);
		break;
	case AF_INET6:
		if (rpc_ntop6_noscopeid(sap, addrbuf, sizeof(addrbuf)) == 0)
			return NULL;
		port = ntohs(((struct sockaddr_in6 *)sap)->sin6_port);
		break;
	default:
		return NULL;
	}

	if (snprintf(portbuf, sizeof(portbuf),
		     ".%u.%u", port >> 8, port & 0xff) > (int)sizeof(portbuf))
		return NULL;

	if (strlcat(addrbuf, portbuf, sizeof(addrbuf)) > sizeof(addrbuf))
		return NULL;

	return kstrdup(addrbuf, gfp_flags);
}