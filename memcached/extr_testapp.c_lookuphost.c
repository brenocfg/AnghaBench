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
struct addrinfo {int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_family; } ;
typedef  int in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EAI_SYSTEM ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct addrinfo *lookuphost(const char *hostname, in_port_t port)
{
    struct addrinfo *ai = 0;
    struct addrinfo hints = { .ai_family = AF_UNSPEC,
                              .ai_protocol = IPPROTO_TCP,
                              .ai_socktype = SOCK_STREAM };
    char service[NI_MAXSERV];
    int error;

    (void)snprintf(service, NI_MAXSERV, "%d", port);
    if ((error = getaddrinfo(hostname, service, &hints, &ai)) != 0) {
       if (error != EAI_SYSTEM) {
          fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(error));
       } else {
          perror("getaddrinfo()");
       }
    }

    return ai;
}