#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svr_sock_addr ;
struct sockaddr_storage {int /*<<< orphan*/  ss_family; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  local_addr ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  sfd; int /*<<< orphan*/  transport; int /*<<< orphan*/  request_addr; } ;
typedef  TYPE_1__ conn ;

/* Variables and functions */
 scalar_t__ IS_UDP (int /*<<< orphan*/ ) ; 
 scalar_t__ conn_closed ; 
 scalar_t__ conn_listening ; 
 scalar_t__ conn_read ; 
 int /*<<< orphan*/  get_conn_text (TYPE_1__ const*,int /*<<< orphan*/ ,char*,struct sockaddr*) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void conn_to_str(const conn *c, char *addr, char *svr_addr) {
    if (!c) {
        strcpy(addr, "<null>");
    } else if (c->state == conn_closed) {
        strcpy(addr, "<closed>");
    } else {
        struct sockaddr_in6 local_addr;
        struct sockaddr *sock_addr = (void *)&c->request_addr;

        /* For listen ports and idle UDP ports, show listen address */
        if (c->state == conn_listening ||
                (IS_UDP(c->transport) &&
                 c->state == conn_read)) {
            socklen_t local_addr_len = sizeof(local_addr);

            if (getsockname(c->sfd,
                        (struct sockaddr *)&local_addr,
                        &local_addr_len) == 0) {
                sock_addr = (struct sockaddr *)&local_addr;
            }
        }
        get_conn_text(c, sock_addr->sa_family, addr, sock_addr);

        if (c->state != conn_listening && !(IS_UDP(c->transport) &&
                 c->state == conn_read)) {
            struct sockaddr_storage svr_sock_addr;
            socklen_t svr_addr_len = sizeof(svr_sock_addr);
            getsockname(c->sfd, (struct sockaddr *)&svr_sock_addr, &svr_addr_len);
            get_conn_text(c, svr_sock_addr.ss_family, svr_addr, (struct sockaddr *)&svr_sock_addr);
        }
    }
}