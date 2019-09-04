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
struct web_client {char* origin; char* cookie1; char* cookie2; int /*<<< orphan*/ * user_agent; int /*<<< orphan*/  ifd; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_WEB_CLIENT ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  web_client_cache_verify (int /*<<< orphan*/ ) ; 
 scalar_t__ web_client_check_tcp (struct web_client*) ; 
 int /*<<< orphan*/  web_client_enable_wait_receive (struct web_client*) ; 
 int /*<<< orphan*/  web_client_update_acl_matches (struct web_client*) ; 
 int /*<<< orphan*/  web_server_log_connection (struct web_client*,char*) ; 

void web_client_initialize_connection(struct web_client *w) {
    int flag = 1;

    if(unlikely(web_client_check_tcp(w) && setsockopt(w->ifd, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int)) != 0))
        debug(D_WEB_CLIENT, "%llu: failed to enable TCP_NODELAY on socket fd %d.", w->id, w->ifd);

    flag = 1;
    if(unlikely(setsockopt(w->ifd, SOL_SOCKET, SO_KEEPALIVE, (char *) &flag, sizeof(int)) != 0))
        debug(D_WEB_CLIENT, "%llu: failed to enable SO_KEEPALIVE on socket fd %d.", w->id, w->ifd);

    web_client_update_acl_matches(w);

    w->origin[0] = '*'; w->origin[1] = '\0';
    w->cookie1[0] = '\0'; w->cookie2[0] = '\0';
    freez(w->user_agent); w->user_agent = NULL;

    web_client_enable_wait_receive(w);

    web_server_log_connection(w, "CONNECTED");

    web_client_cache_verify(0);
}