#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t bucket; int active; int closed; int free; size_t free_bucket; struct TYPE_9__* next; scalar_t__ written; scalar_t__ allocated; scalar_t__ bytes_used; scalar_t__ obj_count; scalar_t__ version; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ store_page ;
struct TYPE_8__ {int /*<<< orphan*/  page_reclaims; int /*<<< orphan*/  bytes_used; int /*<<< orphan*/  objects_used; } ;
struct TYPE_10__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  page_free; TYPE_2__* page_freelist; TYPE_2__** free_page_buckets; TYPE_2__** page_buckets; TYPE_1__ stats; } ;
typedef  TYPE_3__ store_engine ;

/* Variables and functions */
 int /*<<< orphan*/  E_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAT_L (TYPE_3__*) ; 
 int /*<<< orphan*/  STAT_UL (TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _free_page(store_engine *e, store_page *p) {
    store_page *tmp = NULL;
    store_page *prev = NULL;
    E_DEBUG("EXTSTORE: freeing page %u\n", p->id);
    STAT_L(e);
    e->stats.objects_used -= p->obj_count;
    e->stats.bytes_used -= p->bytes_used;
    e->stats.page_reclaims++;
    STAT_UL(e);
    pthread_mutex_lock(&e->mutex);
    // unlink page from bucket list
    tmp = e->page_buckets[p->bucket];
    while (tmp) {
        if (tmp == p) {
            if (prev) {
                prev->next = tmp->next;
            } else {
                e->page_buckets[p->bucket] = tmp->next;
            }
            tmp->next = NULL;
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    // reset most values
    p->version = 0;
    p->obj_count = 0;
    p->bytes_used = 0;
    p->allocated = 0;
    p->written = 0;
    p->bucket = 0;
    p->active = false;
    p->closed = false;
    p->free = true;
    // add to page stack
    // TODO: free_page_buckets first class and remove redundancy?
    if (p->free_bucket != 0) {
        p->next = e->free_page_buckets[p->free_bucket];
        e->free_page_buckets[p->free_bucket] = p;
    } else {
        p->next = e->page_freelist;
        e->page_freelist = p;
    }
    e->page_free++;
    pthread_mutex_unlock(&e->mutex);
}