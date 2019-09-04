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
struct web_client {struct web_client* next; } ;
struct TYPE_2__ {scalar_t__ avail_count; struct web_client* avail; scalar_t__ used_count; struct web_client* used; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdata_thread_disable_cancelability () ; 
 int /*<<< orphan*/  netdata_thread_enable_cancelability () ; 
 int /*<<< orphan*/  web_client_free (struct web_client*) ; 
 TYPE_1__ web_clients_cache ; 

void web_client_cache_destroy(void) {
#ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely(web_clients_cache.pid != 0 && web_clients_cache.pid != gettid()))
        error("Oops! wrong thread accessing the cache. Expected %d, found %d", (int)web_clients_cache.pid, (int)gettid());

    web_client_cache_verify(1);
#endif

    netdata_thread_disable_cancelability();

    struct web_client *w, *t;

    w = web_clients_cache.used;
    while(w) {
        t = w;
        w = w->next;
        web_client_free(t);
    }
    web_clients_cache.used = NULL;
    web_clients_cache.used_count = 0;

    w = web_clients_cache.avail;
    while(w) {
        t = w;
        w = w->next;
        web_client_free(t);
    }
    web_clients_cache.avail = NULL;
    web_clients_cache.avail_count = 0;

    netdata_thread_enable_cancelability();
}