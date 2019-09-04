#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_rbtree_key_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {scalar_t__ inactive; TYPE_6__* shpool; TYPE_1__* sh; } ;
typedef  TYPE_2__ ngx_http_file_cache_t ;
struct TYPE_21__ {int /*<<< orphan*/  key; } ;
struct TYPE_18__ {int uses; int count; scalar_t__ valid_sec; scalar_t__ error; scalar_t__ uniq; int /*<<< orphan*/  queue; scalar_t__ expire; scalar_t__ fs_size; scalar_t__ body_start; scalar_t__ exists; scalar_t__ valid_msec; TYPE_7__ node; int /*<<< orphan*/ * key; } ;
typedef  TYPE_3__ ngx_http_file_cache_node_t ;
struct TYPE_19__ {int min_uses; TYPE_3__* node; scalar_t__ error; scalar_t__ uniq; int /*<<< orphan*/ * key; scalar_t__ body_start; scalar_t__ exists; } ;
typedef  TYPE_4__ ngx_http_cache_t ;
struct TYPE_20__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  log_ctx; } ;
struct TYPE_16__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  rbtree; int /*<<< orphan*/  count; } ;
struct TYPE_15__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_CACHE_KEY_LEN ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_14__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_file_cache_forced_expire (TYPE_2__*) ; 
 TYPE_3__* ngx_http_file_cache_lookup (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_file_cache_set_watermark (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_queue_insert_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_queue_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rbtree_insert (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_slab_calloc_locked (TYPE_6__*,int) ; 
 scalar_t__ ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_http_file_cache_exists(ngx_http_file_cache_t *cache, ngx_http_cache_t *c)
{
    ngx_int_t                    rc;
    ngx_http_file_cache_node_t  *fcn;

    ngx_shmtx_lock(&cache->shpool->mutex);

    fcn = c->node;

    if (fcn == NULL) {
        fcn = ngx_http_file_cache_lookup(cache, c->key);
    }

    if (fcn) {
        ngx_queue_remove(&fcn->queue);

        if (c->node == NULL) {
            fcn->uses++;
            fcn->count++;
        }

        if (fcn->error) {

            if (fcn->valid_sec < ngx_time()) {
                goto renew;
            }

            rc = NGX_OK;

            goto done;
        }

        if (fcn->exists || fcn->uses >= c->min_uses) {

            c->exists = fcn->exists;
            if (fcn->body_start) {
                c->body_start = fcn->body_start;
            }

            rc = NGX_OK;

            goto done;
        }

        rc = NGX_AGAIN;

        goto done;
    }

    fcn = ngx_slab_calloc_locked(cache->shpool,
                                 sizeof(ngx_http_file_cache_node_t));
    if (fcn == NULL) {
        ngx_http_file_cache_set_watermark(cache);

        ngx_shmtx_unlock(&cache->shpool->mutex);

        (void) ngx_http_file_cache_forced_expire(cache);

        ngx_shmtx_lock(&cache->shpool->mutex);

        fcn = ngx_slab_calloc_locked(cache->shpool,
                                     sizeof(ngx_http_file_cache_node_t));
        if (fcn == NULL) {
            ngx_log_error(NGX_LOG_ALERT, ngx_cycle->log, 0,
                          "could not allocate node%s", cache->shpool->log_ctx);
            rc = NGX_ERROR;
            goto failed;
        }
    }

    cache->sh->count++;

    ngx_memcpy((u_char *) &fcn->node.key, c->key, sizeof(ngx_rbtree_key_t));

    ngx_memcpy(fcn->key, &c->key[sizeof(ngx_rbtree_key_t)],
               NGX_HTTP_CACHE_KEY_LEN - sizeof(ngx_rbtree_key_t));

    ngx_rbtree_insert(&cache->sh->rbtree, &fcn->node);

    fcn->uses = 1;
    fcn->count = 1;

renew:

    rc = NGX_DECLINED;

    fcn->valid_msec = 0;
    fcn->error = 0;
    fcn->exists = 0;
    fcn->valid_sec = 0;
    fcn->uniq = 0;
    fcn->body_start = 0;
    fcn->fs_size = 0;

done:

    fcn->expire = ngx_time() + cache->inactive;

    ngx_queue_insert_head(&cache->sh->queue, &fcn->queue);

    c->uniq = fcn->uniq;
    c->error = fcn->error;
    c->node = fcn;

failed:

    ngx_shmtx_unlock(&cache->shpool->mutex);

    return rc;
}