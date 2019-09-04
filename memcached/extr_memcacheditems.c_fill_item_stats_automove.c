#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ age; int /*<<< orphan*/  evicted; int /*<<< orphan*/  outofmemory; } ;
typedef  TYPE_1__ item_stats_automove ;
struct TYPE_7__ {int /*<<< orphan*/  evicted; int /*<<< orphan*/  outofmemory; } ;
struct TYPE_6__ {scalar_t__ time; } ;

/* Variables and functions */
 int COLD_LRU ; 
 int HOT_LRU ; 
 int MAX_NUMBER_OF_SLAB_CLASSES ; 
 scalar_t__ current_time ; 
 TYPE_3__* itemstats ; 
 int /*<<< orphan*/ * lru_locks ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__** tails ; 

void fill_item_stats_automove(item_stats_automove *am) {
    int n;
    for (n = 0; n < MAX_NUMBER_OF_SLAB_CLASSES; n++) {
        item_stats_automove *cur = &am[n];

        // outofmemory records into HOT
        int i = n | HOT_LRU;
        pthread_mutex_lock(&lru_locks[i]);
        cur->outofmemory = itemstats[i].outofmemory;
        pthread_mutex_unlock(&lru_locks[i]);

        // evictions and tail age are from COLD
        i = n | COLD_LRU;
        pthread_mutex_lock(&lru_locks[i]);
        cur->evicted = itemstats[i].evicted;
        if (tails[i]) {
            cur->age = current_time - tails[i]->time;
        } else {
            cur->age = 0;
        }
        pthread_mutex_unlock(&lru_locks[i]);
     }
}