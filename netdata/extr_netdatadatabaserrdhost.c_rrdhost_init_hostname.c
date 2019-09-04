#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* hostname; int /*<<< orphan*/  hash_hostname; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  freez (void*) ; 
 int /*<<< orphan*/  simple_hash (void*) ; 
 int /*<<< orphan*/  strcmp (void*,char const*) ; 
 void* strdupz (char const*) ; 

__attribute__((used)) static inline void rrdhost_init_hostname(RRDHOST *host, const char *hostname) {
    if(host->hostname && hostname && !strcmp(host->hostname, hostname))
        return;

    void *old = host->hostname;
    host->hostname = strdupz(hostname?hostname:"localhost");
    host->hash_hostname = simple_hash(host->hostname);
    freez(old);
}