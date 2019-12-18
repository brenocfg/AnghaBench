#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * s6_addr; } ;
struct sockaddr_in6 {unsigned int sin6_scope_id; TYPE_1__ sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EAI_FAMILY ; 
 int EAI_OVERFLOW ; 
 int /*<<< orphan*/  INIT () ; 
 int /*<<< orphan*/  PFUNC () ; 
 scalar_t__ SOCKFAMILY (struct sockaddr const) ; 
 int /*<<< orphan*/  SOCKPORT (struct sockaddr const) ; 
 int /*<<< orphan*/  inet_ntop (scalar_t__,void const*,char*,int) ; 
 scalar_t__ is_v4inv6 (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proxychains_resolver ; 
 int snprintf (char*,int,char*,int) ; 
 size_t strlen (char*) ; 
 int true_getnameinfo (struct sockaddr const*,int,char*,int,char*,int,int) ; 

int pc_getnameinfo(const struct sockaddr *sa, socklen_t salen,
	           char *host, socklen_t hostlen, char *serv,
	           socklen_t servlen, int flags)
{
	INIT();
	PFUNC();

	if(!proxychains_resolver) {
		return true_getnameinfo(sa, salen, host, hostlen, serv, servlen, flags);
	} else {
		if(!salen || !(SOCKFAMILY(*sa) == AF_INET || SOCKFAMILY(*sa) == AF_INET6))
			return EAI_FAMILY;
		int v6 = SOCKFAMILY(*sa) == AF_INET6;
		if(salen < (v6?sizeof(struct sockaddr_in6):sizeof(struct sockaddr_in)))
			return EAI_FAMILY;
		if(hostlen) {
			unsigned char v4inv6buf[4];
			const void *ip = v6 ? (void*)&((struct sockaddr_in6*)sa)->sin6_addr
			                    : (void*)&((struct sockaddr_in*)sa)->sin_addr;
			unsigned scopeid = 0;
			if(v6) {
				if(is_v4inv6(&((struct sockaddr_in6*)sa)->sin6_addr)) {
					memcpy(v4inv6buf, &((struct sockaddr_in6*)sa)->sin6_addr.s6_addr[12], 4);
					ip = v4inv6buf;
					v6 = 0;
				} else
					scopeid = ((struct sockaddr_in6 *)sa)->sin6_scope_id;
			}
			if(!inet_ntop(v6?AF_INET6:AF_INET,ip,host,hostlen))
				return EAI_OVERFLOW;
			if(scopeid) {
				size_t l = strlen(host);
				if(snprintf(host+l, hostlen-l, "%%%u", scopeid) >= hostlen-l)
					return EAI_OVERFLOW;
			}
		}
		if(servlen) {
			if(snprintf(serv, servlen, "%d", ntohs(SOCKPORT(*sa))) >= servlen)
				return EAI_OVERFLOW;
		}
	}
	return 0;
}