#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct rrdengine_journalfile {int /*<<< orphan*/  datafile; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct pg_cache_page_index* last_page_index; int /*<<< orphan*/  JudyHS_array; } ;
struct page_cache {TYPE_1__ metrics_index; } ;
struct rrdengine_instance {struct page_cache pg_cache; } ;
struct rrdeng_page_descr {struct extent_info* extent; int /*<<< orphan*/ * id; int /*<<< orphan*/  end_time; int /*<<< orphan*/  start_time; int /*<<< orphan*/  page_length; } ;
struct rrdeng_jf_store_data {unsigned int number_of_pages; TYPE_2__* descr; int /*<<< orphan*/  extent_size; int /*<<< orphan*/  extent_offset; } ;
struct pg_cache_page_index {int /*<<< orphan*/  id; struct pg_cache_page_index* prev; } ;
struct extent_info {unsigned int number_of_pages; struct rrdeng_page_descr** pages; int /*<<< orphan*/ * next; int /*<<< orphan*/  datafile; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  end_time; int /*<<< orphan*/  start_time; int /*<<< orphan*/  page_length; scalar_t__ uuid; } ;
typedef  struct pg_cache_page_index* Pvoid_t ;

/* Variables and functions */
 struct pg_cache_page_index** JudyHSGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct pg_cache_page_index** JudyHSIns (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_METRICS ; 
 int /*<<< orphan*/  PJE0 ; 
 int /*<<< orphan*/  assert (int) ; 
 struct pg_cache_page_index* create_page_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  df_extent_insert (struct extent_info*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  freez (struct extent_info*) ; 
 scalar_t__ likely (unsigned int) ; 
 struct extent_info* mallocz (int) ; 
 struct rrdeng_page_descr* pg_cache_create_descr () ; 
 int /*<<< orphan*/  pg_cache_insert (struct rrdengine_instance*,struct pg_cache_page_index*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  uv_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_rdunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void restore_extent_metadata(struct rrdengine_instance *ctx, struct rrdengine_journalfile *journalfile,
                                    void *buf, unsigned max_size)
{
    struct page_cache *pg_cache = &ctx->pg_cache;
    unsigned i, count, payload_length, descr_size, valid_pages;
    struct rrdeng_page_descr *descr;
    struct extent_info *extent;
    /* persistent structures */
    struct rrdeng_jf_store_data *jf_metric_data;

    jf_metric_data = buf;
    count = jf_metric_data->number_of_pages;
    descr_size = sizeof(*jf_metric_data->descr) * count;
    payload_length = sizeof(*jf_metric_data) + descr_size;
    if (payload_length > max_size) {
        error("Corrupted transaction payload.");
        return;
    }

    extent = mallocz(sizeof(*extent) + count * sizeof(extent->pages[0]));
    extent->offset = jf_metric_data->extent_offset;
    extent->size = jf_metric_data->extent_size;
    extent->datafile = journalfile->datafile;
    extent->next = NULL;

    for (i = 0, valid_pages = 0 ; i < count ; ++i) {
        uuid_t *temp_id;
        Pvoid_t *PValue;
        struct pg_cache_page_index *page_index;

        if (PAGE_METRICS != jf_metric_data->descr[i].type) {
            error("Unknown page type encountered.");
            continue;
        }
        temp_id = (uuid_t *)jf_metric_data->descr[i].uuid;

        uv_rwlock_rdlock(&pg_cache->metrics_index.lock);
        PValue = JudyHSGet(pg_cache->metrics_index.JudyHS_array, temp_id, sizeof(uuid_t));
        if (likely(NULL != PValue)) {
            page_index = *PValue;
        }
        uv_rwlock_rdunlock(&pg_cache->metrics_index.lock);
        if (NULL == PValue) {
            /* First time we see the UUID */
            uv_rwlock_wrlock(&pg_cache->metrics_index.lock);
            PValue = JudyHSIns(&pg_cache->metrics_index.JudyHS_array, temp_id, sizeof(uuid_t), PJE0);
            assert(NULL == *PValue); /* TODO: figure out concurrency model */
            *PValue = page_index = create_page_index(temp_id);
            page_index->prev = pg_cache->metrics_index.last_page_index;
            pg_cache->metrics_index.last_page_index = page_index;
            uv_rwlock_wrunlock(&pg_cache->metrics_index.lock);
        }

        descr = pg_cache_create_descr();
        descr->page_length = jf_metric_data->descr[i].page_length;
        descr->start_time = jf_metric_data->descr[i].start_time;
        descr->end_time = jf_metric_data->descr[i].end_time;
        descr->id = &page_index->id;
        descr->extent = extent;
        extent->pages[valid_pages++] = descr;
        pg_cache_insert(ctx, page_index, descr);
    }

    extent->number_of_pages = valid_pages;

    if (likely(valid_pages))
        df_extent_insert(extent);
    else
        freez(extent);
}