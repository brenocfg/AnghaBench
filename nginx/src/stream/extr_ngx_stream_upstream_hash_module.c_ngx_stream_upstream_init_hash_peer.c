#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_stream_upstream_srv_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_4__ ngx_stream_upstream_hash_srv_conf_t ;
struct TYPE_16__ {int /*<<< orphan*/  get_rr_peer; scalar_t__ hash; scalar_t__ rehash; scalar_t__ tries; TYPE_4__* conf; int /*<<< orphan*/  key; int /*<<< orphan*/  rrp; } ;
typedef  TYPE_5__ ngx_stream_upstream_hash_peer_data_t ;
struct TYPE_17__ {TYPE_3__* connection; TYPE_2__* upstream; } ;
typedef  TYPE_6__ ngx_stream_session_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
struct TYPE_12__ {int /*<<< orphan*/  get; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {TYPE_1__ peer; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_STREAM ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_5__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_stream_complex_value (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* ngx_stream_conf_upstream_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_upstream_get_hash_peer ; 
 int /*<<< orphan*/  ngx_stream_upstream_get_round_robin_peer ; 
 int /*<<< orphan*/  ngx_stream_upstream_hash_module ; 
 scalar_t__ ngx_stream_upstream_init_round_robin_peer (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_upstream_init_hash_peer(ngx_stream_session_t *s,
    ngx_stream_upstream_srv_conf_t *us)
{
    ngx_stream_upstream_hash_srv_conf_t   *hcf;
    ngx_stream_upstream_hash_peer_data_t  *hp;

    hp = ngx_palloc(s->connection->pool,
                    sizeof(ngx_stream_upstream_hash_peer_data_t));
    if (hp == NULL) {
        return NGX_ERROR;
    }

    s->upstream->peer.data = &hp->rrp;

    if (ngx_stream_upstream_init_round_robin_peer(s, us) != NGX_OK) {
        return NGX_ERROR;
    }

    s->upstream->peer.get = ngx_stream_upstream_get_hash_peer;

    hcf = ngx_stream_conf_upstream_srv_conf(us,
                                            ngx_stream_upstream_hash_module);

    if (ngx_stream_complex_value(s, &hcf->key, &hp->key) != NGX_OK) {
        return NGX_ERROR;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_STREAM, s->connection->log, 0,
                   "upstream hash key:\"%V\"", &hp->key);

    hp->conf = hcf;
    hp->tries = 0;
    hp->rehash = 0;
    hp->hash = 0;
    hp->get_rr_peer = ngx_stream_upstream_get_round_robin_peer;

    return NGX_OK;
}