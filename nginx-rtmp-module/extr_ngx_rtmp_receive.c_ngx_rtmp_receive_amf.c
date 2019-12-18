#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_amf_elt_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; int /*<<< orphan*/ * link; } ;
typedef  TYPE_3__ ngx_rtmp_amf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
typedef  int /*<<< orphan*/  act ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_rtmp_amf_read (TYPE_3__*,int /*<<< orphan*/ *,size_t) ; 

ngx_int_t
ngx_rtmp_receive_amf(ngx_rtmp_session_t *s, ngx_chain_t *in,
        ngx_rtmp_amf_elt_t *elts, size_t nelts)
{
    ngx_rtmp_amf_ctx_t     act;

    ngx_memzero(&act, sizeof(act));
    act.link = in;
    act.log = s->connection->log;

    return ngx_rtmp_amf_read(&act, elts, nelts);
}