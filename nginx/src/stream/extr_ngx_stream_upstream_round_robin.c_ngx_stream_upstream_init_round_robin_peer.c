#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_13__ {TYPE_9__* data; } ;
struct TYPE_18__ {TYPE_1__ peer; } ;
typedef  TYPE_6__ ngx_stream_upstream_srv_conf_t ;
struct TYPE_19__ {TYPE_9__* peers; scalar_t__* tried; scalar_t__ data; scalar_t__ config; int /*<<< orphan*/ * current; } ;
typedef  TYPE_7__ ngx_stream_upstream_rr_peer_data_t ;
struct TYPE_20__ {TYPE_5__* upstream; TYPE_3__* connection; } ;
typedef  TYPE_8__ ngx_stream_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_21__ {int number; TYPE_2__* next; } ;
struct TYPE_16__ {int /*<<< orphan*/  save_session; int /*<<< orphan*/  set_session; int /*<<< orphan*/  tries; int /*<<< orphan*/  notify; int /*<<< orphan*/  free; int /*<<< orphan*/  get; TYPE_7__* data; } ;
struct TYPE_17__ {TYPE_4__ peer; } ;
struct TYPE_15__ {int /*<<< orphan*/  pool; } ;
struct TYPE_14__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_7__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_stream_upstream_free_round_robin_peer ; 
 int /*<<< orphan*/  ngx_stream_upstream_get_round_robin_peer ; 
 int /*<<< orphan*/  ngx_stream_upstream_notify_round_robin_peer ; 
 int /*<<< orphan*/  ngx_stream_upstream_save_round_robin_peer_session ; 
 int /*<<< orphan*/  ngx_stream_upstream_set_round_robin_peer_session ; 
 int /*<<< orphan*/  ngx_stream_upstream_tries (TYPE_9__*) ; 

ngx_int_t
ngx_stream_upstream_init_round_robin_peer(ngx_stream_session_t *s,
    ngx_stream_upstream_srv_conf_t *us)
{
    ngx_uint_t                           n;
    ngx_stream_upstream_rr_peer_data_t  *rrp;

    rrp = s->upstream->peer.data;

    if (rrp == NULL) {
        rrp = ngx_palloc(s->connection->pool,
                         sizeof(ngx_stream_upstream_rr_peer_data_t));
        if (rrp == NULL) {
            return NGX_ERROR;
        }

        s->upstream->peer.data = rrp;
    }

    rrp->peers = us->peer.data;
    rrp->current = NULL;
    rrp->config = 0;

    n = rrp->peers->number;

    if (rrp->peers->next && rrp->peers->next->number > n) {
        n = rrp->peers->next->number;
    }

    if (n <= 8 * sizeof(uintptr_t)) {
        rrp->tried = &rrp->data;
        rrp->data = 0;

    } else {
        n = (n + (8 * sizeof(uintptr_t) - 1)) / (8 * sizeof(uintptr_t));

        rrp->tried = ngx_pcalloc(s->connection->pool, n * sizeof(uintptr_t));
        if (rrp->tried == NULL) {
            return NGX_ERROR;
        }
    }

    s->upstream->peer.get = ngx_stream_upstream_get_round_robin_peer;
    s->upstream->peer.free = ngx_stream_upstream_free_round_robin_peer;
    s->upstream->peer.notify = ngx_stream_upstream_notify_round_robin_peer;
    s->upstream->peer.tries = ngx_stream_upstream_tries(rrp->peers);
#if (NGX_STREAM_SSL)
    s->upstream->peer.set_session =
                             ngx_stream_upstream_set_round_robin_peer_session;
    s->upstream->peer.save_session =
                             ngx_stream_upstream_save_round_robin_peer_session;
#endif

    return NGX_OK;
}