#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct crawler_expired_data {int /*<<< orphan*/  lock; TYPE_3__* crawlerstats; } ;
typedef  int rel_time_t ;
struct TYPE_17__ {int /*<<< orphan*/  page_version; int /*<<< orphan*/  page_id; } ;
typedef  TYPE_1__ item_hdr ;
struct TYPE_18__ {int it_flags; scalar_t__ exptime; int slabs_clsid; int nkey; } ;
typedef  TYPE_2__ item ;
struct TYPE_19__ {int /*<<< orphan*/ * histo; int /*<<< orphan*/  ttl_hourplus; int /*<<< orphan*/  noexp; int /*<<< orphan*/  seen; int /*<<< orphan*/  reclaimed; } ;
typedef  TYPE_3__ crawlerstats_t ;
struct TYPE_20__ {scalar_t__ data; } ;
typedef  TYPE_4__ crawler_module_t ;
struct TYPE_21__ {int verbose; } ;
struct TYPE_16__ {int /*<<< orphan*/  unfetched; int /*<<< orphan*/  reclaimed; } ;

/* Variables and functions */
 int ITEM_FETCHED ; 
 int ITEM_HDR ; 
 scalar_t__ ITEM_data (TYPE_2__*) ; 
 char* ITEM_key (TYPE_2__*) ; 
 int /*<<< orphan*/  STORAGE_delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_10__* crawlers ; 
 scalar_t__ current_time ; 
 int /*<<< orphan*/  do_item_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  do_item_unlink_nolock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ extstore_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int item_is_flushed (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_decr (TYPE_2__*) ; 
 TYPE_5__ settings ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  storage ; 

__attribute__((used)) static void crawler_expired_eval(crawler_module_t *cm, item *search, uint32_t hv, int i) {
    struct crawler_expired_data *d = (struct crawler_expired_data *) cm->data;
    pthread_mutex_lock(&d->lock);
    crawlerstats_t *s = &d->crawlerstats[i];
    int is_flushed = item_is_flushed(search);
#ifdef EXTSTORE
    bool is_valid = true;
    if (search->it_flags & ITEM_HDR) {
        item_hdr *hdr = (item_hdr *)ITEM_data(search);
        if (extstore_check(storage, hdr->page_id, hdr->page_version) != 0)
            is_valid = false;
    }
#endif
    if ((search->exptime != 0 && search->exptime < current_time)
        || is_flushed
#ifdef EXTSTORE
        || !is_valid
#endif
        ) {
        crawlers[i].reclaimed++;
        s->reclaimed++;

        if (settings.verbose > 1) {
            int ii;
            char *key = ITEM_key(search);
            fprintf(stderr, "LRU crawler found an expired item (flags: %d, slab: %d): ",
                search->it_flags, search->slabs_clsid);
            for (ii = 0; ii < search->nkey; ++ii) {
                fprintf(stderr, "%c", key[ii]);
            }
            fprintf(stderr, "\n");
        }
        if ((search->it_flags & ITEM_FETCHED) == 0 && !is_flushed) {
            crawlers[i].unfetched++;
        }
#ifdef EXTSTORE
        STORAGE_delete(storage, search);
#endif
        do_item_unlink_nolock(search, hv);
        do_item_remove(search);
    } else {
        s->seen++;
        refcount_decr(search);
        if (search->exptime == 0) {
            s->noexp++;
        } else if (search->exptime - current_time > 3599) {
            s->ttl_hourplus++;
        } else {
            rel_time_t ttl_remain = search->exptime - current_time;
            int bucket = ttl_remain / 60;
            if (bucket <= 60) {
                s->histo[bucket]++;
            }
        }
    }
    pthread_mutex_unlock(&d->lock);
}