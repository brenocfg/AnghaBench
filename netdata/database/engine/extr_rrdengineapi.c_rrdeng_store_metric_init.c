#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  temp_id ;
struct TYPE_11__ {int /*<<< orphan*/  lock; struct pg_cache_page_index* last_page_index; int /*<<< orphan*/  JudyHS_array; } ;
struct page_cache {TYPE_4__ metrics_index; } ;
struct rrdengine_instance {struct page_cache pg_cache; } ;
struct rrdeng_collect_handle {struct pg_cache_page_index* page_index; scalar_t__ unaligned_page; int /*<<< orphan*/ * prev_descr; int /*<<< orphan*/ * descr; struct rrdengine_instance* ctx; } ;
struct pg_cache_page_index {int /*<<< orphan*/  id; struct pg_cache_page_index* prev; } ;
struct TYPE_13__ {TYPE_5__* state; TYPE_3__* rrdset; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {struct rrdeng_collect_handle rrdeng; } ;
struct TYPE_12__ {int /*<<< orphan*/ * rrdeng_uuid; TYPE_2__ handle; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; TYPE_1__* rrdhost; } ;
struct TYPE_8__ {struct rrdengine_instance* rrdeng_ctx; } ;
typedef  TYPE_6__ RRDDIM ;
typedef  struct pg_cache_page_index* Pvoid_t ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 struct pg_cache_page_index** JudyHSGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct pg_cache_page_index** JudyHSIns (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PJE0 ; 
 int /*<<< orphan*/  assert (int) ; 
 struct pg_cache_page_index* create_page_index (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_rdunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_wrunlock (int /*<<< orphan*/ *) ; 

void rrdeng_store_metric_init(RRDDIM *rd)
{
    struct rrdeng_collect_handle *handle;
    struct page_cache *pg_cache;
    struct rrdengine_instance *ctx;
    uuid_t temp_id;
    Pvoid_t *PValue;
    struct pg_cache_page_index *page_index;
    EVP_MD_CTX *evpctx;
    unsigned char hash_value[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    //&default_global_ctx; TODO: test this use case or remove it?

    ctx = rd->rrdset->rrdhost->rrdeng_ctx;
    pg_cache = &ctx->pg_cache;
    handle = &rd->state->handle.rrdeng;
    handle->ctx = ctx;

    evpctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(evpctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(evpctx, rd->id, strlen(rd->id));
    EVP_DigestUpdate(evpctx, rd->rrdset->id, strlen(rd->rrdset->id));
    EVP_DigestFinal_ex(evpctx, hash_value, &hash_len);
    EVP_MD_CTX_destroy(evpctx);
    assert(hash_len > sizeof(temp_id));
    memcpy(&temp_id, hash_value, sizeof(temp_id));

    handle->descr = NULL;
    handle->prev_descr = NULL;
    handle->unaligned_page = 0;

    uv_rwlock_rdlock(&pg_cache->metrics_index.lock);
    PValue = JudyHSGet(pg_cache->metrics_index.JudyHS_array, &temp_id, sizeof(uuid_t));
    if (likely(NULL != PValue)) {
        page_index = *PValue;
    }
    uv_rwlock_rdunlock(&pg_cache->metrics_index.lock);
    if (NULL == PValue) {
        /* First time we see the UUID */
        uv_rwlock_wrlock(&pg_cache->metrics_index.lock);
        PValue = JudyHSIns(&pg_cache->metrics_index.JudyHS_array, &temp_id, sizeof(uuid_t), PJE0);
        assert(NULL == *PValue); /* TODO: figure out concurrency model */
        *PValue = page_index = create_page_index(&temp_id);
        page_index->prev = pg_cache->metrics_index.last_page_index;
        pg_cache->metrics_index.last_page_index = page_index;
        uv_rwlock_wrunlock(&pg_cache->metrics_index.lock);
    }
    rd->state->rrdeng_uuid = &page_index->id;
    handle->page_index = page_index;
}