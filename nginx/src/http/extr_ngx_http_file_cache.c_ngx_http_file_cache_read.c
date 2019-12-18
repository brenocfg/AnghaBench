#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ time_t ;
typedef  scalar_t__ ssize_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_22__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_10__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_23__ {int cached; TYPE_8__* connection; } ;
typedef  TYPE_11__ ngx_http_request_t ;
struct TYPE_24__ {TYPE_4__* shpool; TYPE_2__* sh; } ;
typedef  TYPE_12__ ngx_http_file_cache_t ;
typedef  int /*<<< orphan*/  ngx_http_file_cache_key ;
struct TYPE_25__ {scalar_t__ version; scalar_t__ crc32; size_t body_start; scalar_t__ vary_len; scalar_t__ valid_sec; scalar_t__ updating_sec; scalar_t__ error_sec; int /*<<< orphan*/  etag; int /*<<< orphan*/  etag_len; int /*<<< orphan*/  valid_msec; int /*<<< orphan*/  date; int /*<<< orphan*/  last_modified; int /*<<< orphan*/  variant; int /*<<< orphan*/  vary; scalar_t__ header_start; } ;
typedef  TYPE_13__ ngx_http_file_cache_header_t ;
struct TYPE_27__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_32__ {int /*<<< orphan*/  data; } ;
struct TYPE_33__ {TYPE_6__ name; } ;
struct TYPE_31__ {size_t nelts; TYPE_10__* elts; } ;
struct TYPE_26__ {size_t header_start; scalar_t__ crc32; size_t body_start; scalar_t__ valid_sec; scalar_t__ updating_sec; scalar_t__ error_sec; int stale_updating; int stale_error; int updating; TYPE_3__* node; int /*<<< orphan*/  lock_time; scalar_t__ fs_size; int /*<<< orphan*/  uniq; TYPE_12__* file_cache; TYPE_1__ etag; int /*<<< orphan*/  valid_msec; int /*<<< orphan*/  date; int /*<<< orphan*/  last_modified; TYPE_9__* buf; int /*<<< orphan*/ * variant; TYPE_7__ file; TYPE_5__ keys; } ;
typedef  TYPE_14__ ngx_http_cache_t ;
struct TYPE_35__ {int /*<<< orphan*/  last; int /*<<< orphan*/ * pos; } ;
struct TYPE_34__ {int /*<<< orphan*/  log; } ;
struct TYPE_30__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_29__ {int exists; int uses; size_t body_start; int updating; int /*<<< orphan*/  lock_time; scalar_t__ fs_size; int /*<<< orphan*/  uniq; } ;
struct TYPE_28__ {int /*<<< orphan*/  size; scalar_t__ cold; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_HTTP_CACHE_KEY_LEN ; 
 scalar_t__ NGX_HTTP_CACHE_STALE ; 
 scalar_t__ NGX_HTTP_CACHE_UPDATING ; 
 scalar_t__ NGX_HTTP_CACHE_VARY_LEN ; 
 scalar_t__ NGX_HTTP_CACHE_VERSION ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_file_cache_aio_read (TYPE_11__*,TYPE_14__*) ; 
 scalar_t__ ngx_http_file_cache_reopen (TYPE_11__*,TYPE_14__*) ; 
 int /*<<< orphan*/  ngx_http_file_cache_vary (TYPE_11__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_http_file_cache_read(ngx_http_request_t *r, ngx_http_cache_t *c)
{
    u_char                        *p;
    time_t                         now;
    ssize_t                        n;
    ngx_str_t                     *key;
    ngx_int_t                      rc;
    ngx_uint_t                     i;
    ngx_http_file_cache_t         *cache;
    ngx_http_file_cache_header_t  *h;

    n = ngx_http_file_cache_aio_read(r, c);

    if (n < 0) {
        return n;
    }

    if ((size_t) n < c->header_start) {
        ngx_log_error(NGX_LOG_CRIT, r->connection->log, 0,
                      "cache file \"%s\" is too small", c->file.name.data);
        return NGX_DECLINED;
    }

    h = (ngx_http_file_cache_header_t *) c->buf->pos;

    if (h->version != NGX_HTTP_CACHE_VERSION) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "cache file \"%s\" version mismatch", c->file.name.data);
        return NGX_DECLINED;
    }

    if (h->crc32 != c->crc32 || (size_t) h->header_start != c->header_start) {
        ngx_log_error(NGX_LOG_CRIT, r->connection->log, 0,
                      "cache file \"%s\" has md5 collision", c->file.name.data);
        return NGX_DECLINED;
    }

    p = c->buf->pos + sizeof(ngx_http_file_cache_header_t)
        + sizeof(ngx_http_file_cache_key);

    key = c->keys.elts;
    for (i = 0; i < c->keys.nelts; i++) {
        if (ngx_memcmp(p, key[i].data, key[i].len) != 0) {
            ngx_log_error(NGX_LOG_CRIT, r->connection->log, 0,
                          "cache file \"%s\" has md5 collision",
                          c->file.name.data);
            return NGX_DECLINED;
        }

        p += key[i].len;
    }

    if ((size_t) h->body_start > c->body_start) {
        ngx_log_error(NGX_LOG_CRIT, r->connection->log, 0,
                      "cache file \"%s\" has too long header",
                      c->file.name.data);
        return NGX_DECLINED;
    }

    if (h->vary_len > NGX_HTTP_CACHE_VARY_LEN) {
        ngx_log_error(NGX_LOG_CRIT, r->connection->log, 0,
                      "cache file \"%s\" has incorrect vary length",
                      c->file.name.data);
        return NGX_DECLINED;
    }

    if (h->vary_len) {
        ngx_http_file_cache_vary(r, h->vary, h->vary_len, c->variant);

        if (ngx_memcmp(c->variant, h->variant, NGX_HTTP_CACHE_KEY_LEN) != 0) {
            ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "http file cache vary mismatch");
            return ngx_http_file_cache_reopen(r, c);
        }
    }

    c->buf->last += n;

    c->valid_sec = h->valid_sec;
    c->updating_sec = h->updating_sec;
    c->error_sec = h->error_sec;
    c->last_modified = h->last_modified;
    c->date = h->date;
    c->valid_msec = h->valid_msec;
    c->body_start = h->body_start;
    c->etag.len = h->etag_len;
    c->etag.data = h->etag;

    r->cached = 1;

    cache = c->file_cache;

    if (cache->sh->cold) {

        ngx_shmtx_lock(&cache->shpool->mutex);

        if (!c->node->exists) {
            c->node->uses = 1;
            c->node->body_start = c->body_start;
            c->node->exists = 1;
            c->node->uniq = c->uniq;
            c->node->fs_size = c->fs_size;

            cache->sh->size += c->fs_size;
        }

        ngx_shmtx_unlock(&cache->shpool->mutex);
    }

    now = ngx_time();

    if (c->valid_sec < now) {
        c->stale_updating = c->valid_sec + c->updating_sec >= now;
        c->stale_error = c->valid_sec + c->error_sec >= now;

        ngx_shmtx_lock(&cache->shpool->mutex);

        if (c->node->updating) {
            rc = NGX_HTTP_CACHE_UPDATING;

        } else {
            c->node->updating = 1;
            c->updating = 1;
            c->lock_time = c->node->lock_time;
            rc = NGX_HTTP_CACHE_STALE;
        }

        ngx_shmtx_unlock(&cache->shpool->mutex);

        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http file cache expired: %i %T %T",
                       rc, c->valid_sec, now);

        return rc;
    }

    return NGX_OK;
}