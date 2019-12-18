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
struct TYPE_2__ {int /*<<< orphan*/  reuse_port; int /*<<< orphan*/  listener; } ;
struct lwan {TYPE_1__ config; } ;
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_socktype; } ;
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int bind_and_listen_addrinfos (struct addrinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  lwan_status_critical (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_listener (char*,char**,char**) ; 
 char* strdupa (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_socket_normally(struct lwan *l)
{
    char *node, *port;
    char *listener = strdupa(l->config.listener);
    sa_family_t family = parse_listener(listener, &node, &port);
    if (family == AF_UNSPEC)
        lwan_status_critical("Could not parse listener: %s",
                             l->config.listener);

    struct addrinfo *addrs;
    struct addrinfo hints = {.ai_family = family,
                             .ai_socktype = SOCK_STREAM,
                             .ai_flags = AI_PASSIVE};

    int ret = getaddrinfo(node, port, &hints, &addrs);
    if (ret)
        lwan_status_critical("getaddrinfo: %s", gai_strerror(ret));

    int fd = bind_and_listen_addrinfos(addrs, l->config.reuse_port);
    freeaddrinfo(addrs);
    return fd;
}