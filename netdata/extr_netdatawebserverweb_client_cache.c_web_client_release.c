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
struct web_client {int ifd; int ofd; struct web_client* prev; struct web_client* next; int /*<<< orphan*/  client_port; int /*<<< orphan*/  client_ip; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int used_count; int avail_count; struct web_client* avail; struct web_client* used; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_WEB_CLIENT_ACCESS ; 
 scalar_t__ WEB_SERVER_MODE_STATIC_THREADED ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdata_thread_disable_cancelability () ; 
 int /*<<< orphan*/  netdata_thread_enable_cancelability () ; 
 int /*<<< orphan*/  web_client_disconnected () ; 
 int /*<<< orphan*/  web_client_free (struct web_client*) ; 
 int /*<<< orphan*/  web_client_request_done (struct web_client*) ; 
 TYPE_1__ web_clients_cache ; 
 int /*<<< orphan*/  web_server_log_connection (struct web_client*,char*) ; 
 scalar_t__ web_server_mode ; 

void web_client_release(struct web_client *w) {
#ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely(web_clients_cache.pid != 0 && web_clients_cache.pid != gettid()))
        error("Oops! wrong thread accessing the cache. Expected %d, found %d", (int)web_clients_cache.pid, (int)gettid());

    if(unlikely(w->running))
        error("%llu: releasing web client from %s port %s, but it still running.", w->id, w->client_ip, w->client_port);
#endif

    debug(D_WEB_CLIENT_ACCESS, "%llu: Closing web client from %s port %s.", w->id, w->client_ip, w->client_port);

    web_server_log_connection(w, "DISCONNECTED");
    web_client_request_done(w);
    web_client_disconnected();

    netdata_thread_disable_cancelability();

    if(web_server_mode != WEB_SERVER_MODE_STATIC_THREADED) {
        if (w->ifd != -1) close(w->ifd);
        if (w->ofd != -1 && w->ofd != w->ifd) close(w->ofd);
        w->ifd = w->ofd = -1;
    }

    // unlink it from the used
    if (w == web_clients_cache.used) web_clients_cache.used = w->next;
    if(w->prev) w->prev->next = w->next;
    if(w->next) w->next->prev = w->prev;
    web_clients_cache.used_count--;

    if(web_clients_cache.avail_count >= 2 * web_clients_cache.used_count) {
        // we have too many of them - free it
        web_client_free(w);
    }
    else {
        // link it to the avail
        if (web_clients_cache.avail) web_clients_cache.avail->prev = w;
        w->next = web_clients_cache.avail;
        w->prev = NULL;
        web_clients_cache.avail = w;
        web_clients_cache.avail_count++;
    }

    netdata_thread_enable_cancelability();
}