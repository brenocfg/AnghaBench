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
struct TYPE_9__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_core_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_amf_elt_t ;
struct TYPE_10__ {int /*<<< orphan*/ * link; int /*<<< orphan*/ * first; int /*<<< orphan*/  log; int /*<<< orphan*/  alloc; int /*<<< orphan*/ * arg; } ;
typedef  TYPE_3__ ngx_rtmp_amf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
typedef  int /*<<< orphan*/  act ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_rtmp_alloc_amf_buf ; 
 int /*<<< orphan*/  ngx_rtmp_amf_write (TYPE_3__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/ * ngx_rtmp_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_rtmp_append_amf(ngx_rtmp_session_t *s,
                    ngx_chain_t **first, ngx_chain_t **last,
                    ngx_rtmp_amf_elt_t *elts, size_t nelts)
{
    ngx_rtmp_amf_ctx_t          act;
    ngx_rtmp_core_srv_conf_t   *cscf;
    ngx_int_t                   rc;

    cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);

    memset(&act, 0, sizeof(act));
    act.arg = cscf;
    act.alloc = ngx_rtmp_alloc_amf_buf;
    act.log = s->connection->log;

    if (first) {
        act.first = *first;
    }

    if (last) {
        act.link = *last;
    }

    rc = ngx_rtmp_amf_write(&act, elts, nelts);

    if (first) {
        *first = act.first;
    }

    if (last) {
        *last = act.link;
    }

    return rc;
}