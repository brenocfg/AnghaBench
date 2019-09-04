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
struct TYPE_2__ {int allocated; int reused; int /*<<< orphan*/  avail_count; int /*<<< orphan*/  used_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_1__ web_clients_cache ; 

inline void web_client_cache_verify(int force) {
#ifdef NETDATA_INTERNAL_CHECKS
    static __thread size_t count = 0;
    count++;

    if(unlikely(force || count > 1000)) {
        count = 0;

        struct web_client *w;
        size_t used = 0, avail = 0;
        for(w = web_clients_cache.used; w ; w = w->next) used++;
        for(w = web_clients_cache.avail; w ; w = w->next) avail++;

        info("web_client_cache has %zu (%zu) used and %zu (%zu) available clients, allocated %zu, reused %zu (hit %zu%%)."
             , used, web_clients_cache.used_count
             , avail, web_clients_cache.avail_count
             , web_clients_cache.allocated
             , web_clients_cache.reused
             , (web_clients_cache.allocated + web_clients_cache.reused)?(web_clients_cache.reused * 100 / (web_clients_cache.allocated + web_clients_cache.reused)):0
        );
    }
#else
    if(unlikely(force)) {
        info("web_client_cache has %zu used and %zu available clients, allocated %zu, reused %zu (hit %zu%%)."
             , web_clients_cache.used_count
             , web_clients_cache.avail_count
             , web_clients_cache.allocated
             , web_clients_cache.reused
             , (web_clients_cache.allocated + web_clients_cache.reused)?(web_clients_cache.reused * 100 / (web_clients_cache.allocated + web_clients_cache.reused)):0
            );
    }
#endif
}