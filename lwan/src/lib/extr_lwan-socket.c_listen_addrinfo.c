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
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  serv_buf ;
typedef  int /*<<< orphan*/  host_buf ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  get_backlog_size () ; 
 int getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_status_critical (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*) ; 
 int /*<<< orphan*/  lwan_status_info (char*,char*,char*) ; 
 int set_socket_flags (int) ; 

__attribute__((used)) static int listen_addrinfo(int fd, const struct addrinfo *addr)
{
    if (listen(fd, get_backlog_size()) < 0)
        lwan_status_critical_perror("listen");

    char host_buf[NI_MAXHOST], serv_buf[NI_MAXSERV];
    int ret = getnameinfo(addr->ai_addr, addr->ai_addrlen, host_buf,
                          sizeof(host_buf), serv_buf, sizeof(serv_buf),
                          NI_NUMERICHOST | NI_NUMERICSERV);
    if (ret)
        lwan_status_critical("getnameinfo: %s", gai_strerror(ret));

    if (addr->ai_family == AF_INET6)
        lwan_status_info("Listening on http://[%s]:%s", host_buf, serv_buf);
    else
        lwan_status_info("Listening on http://%s:%s", host_buf, serv_buf);

    return set_socket_flags(fd);
}