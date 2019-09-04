#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t count; struct TYPE_5__* master; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ redisCachedCluster ;

/* Variables and functions */
 int /*<<< orphan*/  cluster_free_cached_master (TYPE_1__*) ; 
 int /*<<< orphan*/  pefree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ ) ; 

void cluster_cache_free(redisCachedCluster *rcc) {
    size_t i;

    /* Free masters */
    for (i = 0; i < rcc->count; i++) {
        cluster_free_cached_master(&rcc->master[i]);
    }

    /* Free hash key */
    zend_string_release(rcc->hash);
    pefree(rcc->master, 1);
    pefree(rcc, 1);
}