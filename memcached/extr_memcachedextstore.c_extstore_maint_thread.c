#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct extstore_page_data {scalar_t__ free_bucket; scalar_t__ version; int /*<<< orphan*/  bucket; scalar_t__ bytes_used; } ;
struct TYPE_10__ {size_t id; scalar_t__ free_bucket; scalar_t__ obj_count; int closed; scalar_t__ version; scalar_t__ refcount; int /*<<< orphan*/  mutex; scalar_t__ bytes_used; int /*<<< orphan*/  bucket; scalar_t__ free; scalar_t__ active; } ;
typedef  TYPE_2__ store_page ;
struct TYPE_11__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; TYPE_4__* e; } ;
typedef  TYPE_3__ store_maint_thread ;
struct TYPE_9__ {int /*<<< orphan*/  page_data; int /*<<< orphan*/  bytes_evicted; int /*<<< orphan*/  objects_evicted; int /*<<< orphan*/  page_evictions; } ;
struct TYPE_12__ {int page_count; scalar_t__ page_free; TYPE_1__ stats; TYPE_2__* pages; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * page_freelist; } ;
typedef  TYPE_4__ store_engine ;

/* Variables and functions */
 int /*<<< orphan*/  E_DEBUG (char*,size_t,unsigned long long) ; 
 int /*<<< orphan*/  STAT_L (TYPE_4__*) ; 
 int /*<<< orphan*/  STAT_UL (TYPE_4__*) ; 
 scalar_t__ ULLONG_MAX ; 
 int /*<<< orphan*/  _free_page (TYPE_4__*,TYPE_2__*) ; 
 struct extstore_page_data* calloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct extstore_page_data*,int) ; 
 int /*<<< orphan*/  memset (struct extstore_page_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *extstore_maint_thread(void *arg) {
    store_maint_thread *me = (store_maint_thread *)arg;
    store_engine *e = me->e;
    struct extstore_page_data *pd =
        calloc(e->page_count, sizeof(struct extstore_page_data));
    pthread_mutex_lock(&me->mutex);
    while (1) {
        int i;
        bool do_evict = false;
        unsigned int low_page = 0;
        uint64_t low_version = ULLONG_MAX;

        pthread_cond_wait(&me->cond, &me->mutex);
        pthread_mutex_lock(&e->mutex);
        // default freelist requires at least one page free.
        // specialized freelists fall back to default once full.
        if (e->page_free == 0 || e->page_freelist == NULL) {
            do_evict = true;
        }
        pthread_mutex_unlock(&e->mutex);
        memset(pd, 0, sizeof(struct extstore_page_data) * e->page_count);

        for (i = 0; i < e->page_count; i++) {
            store_page *p = &e->pages[i];
            pthread_mutex_lock(&p->mutex);
            pd[p->id].free_bucket = p->free_bucket;
            if (p->active || p->free) {
                pthread_mutex_unlock(&p->mutex);
                continue;
            }
            if (p->obj_count > 0 && !p->closed) {
                pd[p->id].version = p->version;
                pd[p->id].bytes_used = p->bytes_used;
                pd[p->id].bucket = p->bucket;
                // low_version/low_page are only used in the eviction
                // scenario. when we evict, it's only to fill the default page
                // bucket again.
                // TODO: experiment with allowing evicting up to a single page
                // for any specific free bucket. this is *probably* required
                // since it could cause a load bias on default-only devices?
                if (p->free_bucket == 0 && p->version < low_version) {
                    low_version = p->version;
                    low_page = i;
                }
            }
            if ((p->obj_count == 0 || p->closed) && p->refcount == 0) {
                _free_page(e, p);
                // Found a page to free, no longer need to evict.
                do_evict = false;
            }
            pthread_mutex_unlock(&p->mutex);
        }

        if (do_evict && low_version != ULLONG_MAX) {
            store_page *p = &e->pages[low_page];
            E_DEBUG("EXTSTORE: evicting page [%d] [v: %llu]\n",
                    p->id, (unsigned long long) p->version);
            pthread_mutex_lock(&p->mutex);
            if (!p->closed) {
                p->closed = true;
                STAT_L(e);
                e->stats.page_evictions++;
                e->stats.objects_evicted += p->obj_count;
                e->stats.bytes_evicted += p->bytes_used;
                STAT_UL(e);
                if (p->refcount == 0) {
                    _free_page(e, p);
                }
            }
            pthread_mutex_unlock(&p->mutex);
        }

        // copy the page data into engine context so callers can use it from
        // the stats lock.
        STAT_L(e);
        memcpy(e->stats.page_data, pd,
                sizeof(struct extstore_page_data) * e->page_count);
        STAT_UL(e);
    }

    return NULL;
}