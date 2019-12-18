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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct addrinfo {struct addrinfo* ai_next; TYPE_1__* ai_addr; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sadr ;
struct TYPE_2__ {int sa_family; } ;
typedef  int /*<<< orphan*/  SIMPLE_PATTERN ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  D_LISTENER ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  NI_NAMEREQD ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  error (char*,char const*,char*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 scalar_t__ getaddrinfo (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int getnameinfo (struct sockaddr*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getpeername (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  inet_ntop (int const,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ simple_pattern_matches (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

extern int connection_allowed(int fd, char *client_ip, char *client_host, size_t hostsize, SIMPLE_PATTERN *access_list,
                              const char *patname, int allow_dns)
{
    debug(D_LISTENER,"checking %s... (allow_dns=%d)", patname, allow_dns);
    if (!access_list)
        return 1;
    if (simple_pattern_matches(access_list, client_ip))
        return 1;
    // If the hostname is unresolved (and needed) then attempt the DNS lookups.
    //if (client_host[0]==0 && simple_pattern_is_potential_name(access_list))
    if (client_host[0]==0 && allow_dns)
    {
        struct sockaddr_storage sadr;
        socklen_t addrlen = sizeof(sadr);
        int err = getpeername(fd, (struct sockaddr*)&sadr, &addrlen);
        if (err != 0 ||
            (err = getnameinfo((struct sockaddr *)&sadr, addrlen, client_host, (socklen_t)hostsize,
                              NULL, 0, NI_NAMEREQD)) != 0) {
            error("Incoming %s on '%s' does not match a numeric pattern, and host could not be resolved (err=%s)",
                  patname, client_ip, gai_strerror(err));
            if (hostsize >= 8)
                strcpy(client_host,"UNKNOWN");
            return 0;
        }
        struct addrinfo *addr_infos = NULL;
        if (getaddrinfo(client_host, NULL, NULL, &addr_infos) !=0 ) {
            error("LISTENER: cannot validate hostname '%s' from '%s' by resolving it",
                  client_host, client_ip);
            if (hostsize >= 8)
                strcpy(client_host,"UNKNOWN");
            return 0;
        }
        struct addrinfo *scan = addr_infos;
        int    validated = 0;
        while (scan) {
            char address[INET6_ADDRSTRLEN];
            address[0] = 0;
            switch (scan->ai_addr->sa_family) {
                case AF_INET:
                    inet_ntop(AF_INET, &((struct sockaddr_in*)(scan->ai_addr))->sin_addr, address, INET6_ADDRSTRLEN);
                    break;
                case AF_INET6:
                    inet_ntop(AF_INET6, &((struct sockaddr_in6*)(scan->ai_addr))->sin6_addr, address, INET6_ADDRSTRLEN);
                    break;
            }
            debug(D_LISTENER, "Incoming ip %s rev-resolved onto %s, validating against forward-resolution %s",
                  client_ip, client_host, address);
            if (!strcmp(client_ip, address)) {
                validated = 1;
                break;
            }
            scan = scan->ai_next;
        }
        if (!validated) {
            error("LISTENER: Cannot validate '%s' as ip of '%s', not listed in DNS", client_ip, client_host);
            if (hostsize >= 8)
                strcpy(client_host,"UNKNOWN");
        }
        if (addr_infos!=NULL)
            freeaddrinfo(addr_infos);
    }
    if (!simple_pattern_matches(access_list, client_host)) {
        debug(D_LISTENER, "Incoming connection on '%s' (%s) does not match allowed pattern for %s",
              client_ip, client_host, patname);
        return 0;
    }
    return 1;
}