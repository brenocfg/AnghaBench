#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  slabs; int /*<<< orphan*/  sl_curr; int /*<<< orphan*/  perslab; } ;
typedef  TYPE_1__ slabclass_t ;
struct TYPE_6__ {int /*<<< orphan*/  chunk_size; int /*<<< orphan*/  total_pages; int /*<<< orphan*/  free_chunks; int /*<<< orphan*/  chunks_per_page; } ;
typedef  TYPE_2__ slab_stats_automove ;

/* Variables and functions */
 int MAX_NUMBER_OF_SLAB_CLASSES ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* slabclass ; 
 int /*<<< orphan*/  slabs_lock ; 

void fill_slab_stats_automove(slab_stats_automove *am) {
    int n;
    pthread_mutex_lock(&slabs_lock);
    for (n = 0; n < MAX_NUMBER_OF_SLAB_CLASSES; n++) {
        slabclass_t *p = &slabclass[n];
        slab_stats_automove *cur = &am[n];
        cur->chunks_per_page = p->perslab;
        cur->free_chunks = p->sl_curr;
        cur->total_pages = p->slabs;
        cur->chunk_size = p->size;
    }
    pthread_mutex_unlock(&slabs_lock);
}