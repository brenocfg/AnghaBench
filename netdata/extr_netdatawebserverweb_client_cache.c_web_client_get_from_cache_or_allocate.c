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
struct web_client {int /*<<< orphan*/  mode; int /*<<< orphan*/  id; struct web_client* prev; struct web_client* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  used_count; struct web_client* used; int /*<<< orphan*/  allocated; int /*<<< orphan*/  reused; int /*<<< orphan*/  avail_count; struct web_client* avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  WEB_CLIENT_MODE_NORMAL ; 
 int /*<<< orphan*/  netdata_thread_disable_cancelability () ; 
 int /*<<< orphan*/  netdata_thread_enable_cancelability () ; 
 struct web_client* web_client_alloc () ; 
 int /*<<< orphan*/  web_client_connected () ; 
 int /*<<< orphan*/  web_client_zero (struct web_client*) ; 
 TYPE_1__ web_clients_cache ; 

struct web_client *web_client_get_from_cache_or_allocate() {

#ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely(web_clients_cache.pid == 0))
        web_clients_cache.pid = gettid();

    if(unlikely(web_clients_cache.pid != 0 && web_clients_cache.pid != gettid()))
        error("Oops! wrong thread accessing the cache. Expected %d, found %d", (int)web_clients_cache.pid, (int)gettid());
#endif

    netdata_thread_disable_cancelability();

    struct web_client *w = web_clients_cache.avail;

    if(w) {
        // get it from avail
        if (w == web_clients_cache.avail) web_clients_cache.avail = w->next;
        if(w->prev) w->prev->next = w->next;
        if(w->next) w->next->prev = w->prev;
        web_clients_cache.avail_count--;
        web_client_zero(w);
        web_clients_cache.reused++;
    }
    else {
        // allocate it
        w = web_client_alloc();
        web_clients_cache.allocated++;
    }

    // link it to used web clients
    if (web_clients_cache.used) web_clients_cache.used->prev = w;
    w->next = web_clients_cache.used;
    w->prev = NULL;
    web_clients_cache.used = w;
    web_clients_cache.used_count++;

    // initialize it
    w->id = web_client_connected();
    w->mode = WEB_CLIENT_MODE_NORMAL;

    netdata_thread_enable_cancelability();

    return w;
}