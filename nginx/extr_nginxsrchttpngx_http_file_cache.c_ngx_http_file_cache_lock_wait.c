#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int ngx_msec_t ;
typedef  scalar_t__ ngx_msec_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* write_event_handler ) (TYPE_5__*) ;TYPE_4__* main; TYPE_1__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_16__ {TYPE_3__* shpool; } ;
typedef  TYPE_6__ ngx_http_file_cache_t ;
struct TYPE_17__ {int wait_time; scalar_t__ waiting; int /*<<< orphan*/  wait_event; TYPE_2__* node; TYPE_6__* file_cache; scalar_t__ lock_timeout; } ;
typedef  TYPE_7__ ngx_http_cache_t ;
struct TYPE_14__ {int /*<<< orphan*/  blocked; } ;
struct TYPE_13__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_12__ {int lock_time; scalar_t__ updating; } ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  ngx_add_timer (int /*<<< orphan*/ *,int) ; 
 int ngx_current_msec ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static void
ngx_http_file_cache_lock_wait(ngx_http_request_t *r, ngx_http_cache_t *c)
{
    ngx_uint_t              wait;
    ngx_msec_t              now, timer;
    ngx_http_file_cache_t  *cache;

    now = ngx_current_msec;

    timer = c->wait_time - now;

    if ((ngx_msec_int_t) timer <= 0) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "cache lock timeout");
        c->lock_timeout = 0;
        goto wakeup;
    }

    cache = c->file_cache;
    wait = 0;

    ngx_shmtx_lock(&cache->shpool->mutex);

    timer = c->node->lock_time - now;

    if (c->node->updating && (ngx_msec_int_t) timer > 0) {
        wait = 1;
    }

    ngx_shmtx_unlock(&cache->shpool->mutex);

    if (wait) {
        ngx_add_timer(&c->wait_event, (timer > 500) ? 500 : timer);
        return;
    }

wakeup:

    c->waiting = 0;
    r->main->blocked--;
    r->write_event_handler(r);
}