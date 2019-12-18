#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_22__ {TYPE_2__* connection; scalar_t__ relay; scalar_t__ auto_pushed; } ;
typedef  TYPE_5__ ngx_rtmp_session_t ;
struct TYPE_23__ {scalar_t__ disk_full_time; TYPE_4__* format; } ;
typedef  TYPE_6__ ngx_rtmp_log_t ;
struct TYPE_24__ {int /*<<< orphan*/ * (* getdata ) (TYPE_5__*,int /*<<< orphan*/ *,TYPE_7__*) ;scalar_t__ (* getlen ) (TYPE_5__*,TYPE_7__*) ;} ;
typedef  TYPE_7__ ngx_rtmp_log_op_t ;
struct TYPE_25__ {TYPE_1__* logs; scalar_t__ off; } ;
typedef  TYPE_8__ ngx_rtmp_log_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_header_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_21__ {TYPE_3__* ops; } ;
struct TYPE_20__ {scalar_t__ nelts; TYPE_7__* elts; } ;
struct TYPE_19__ {int /*<<< orphan*/  pool; } ;
struct TYPE_18__ {scalar_t__ nelts; TYPE_6__* elts; } ;

/* Variables and functions */
 scalar_t__ NGX_LINEFEED_SIZE ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_linefeed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 TYPE_8__* ngx_rtmp_get_module_app_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_log_module ; 
 int /*<<< orphan*/  ngx_rtmp_log_write (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ngx_time () ; 
 scalar_t__ stub1 (TYPE_5__*,TYPE_7__*) ; 
 int /*<<< orphan*/ * stub2 (TYPE_5__*,int /*<<< orphan*/ *,TYPE_7__*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_log_disconnect(ngx_rtmp_session_t *s, ngx_rtmp_header_t *h,
                        ngx_chain_t *in)
{
    ngx_rtmp_log_app_conf_t    *lacf;
    ngx_rtmp_log_t             *log;
    ngx_rtmp_log_op_t          *op;
    ngx_uint_t                  n, i;
    u_char                     *line, *p;
    size_t                      len;

    if (s->auto_pushed || s->relay) {
        return NGX_OK;
    }

    lacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_log_module);
    if (lacf == NULL || lacf->off || lacf->logs == NULL) {
        return NGX_OK;
    }

    log = lacf->logs->elts;
    for (i = 0; i < lacf->logs->nelts; ++i, ++log) {

        if (ngx_time() == log->disk_full_time) {
            /* FreeBSD full disk protection;
             * nginx http logger does the same */
            continue;
        }

        len = 0;
        op = log->format->ops->elts;
        for (n = 0; n < log->format->ops->nelts; ++n, ++op) {
            len += op->getlen(s, op);
        }

        len += NGX_LINEFEED_SIZE;

        line = ngx_palloc(s->connection->pool, len);
        if (line == NULL) {
            return NGX_OK;
        }

        p = line;
        op = log->format->ops->elts;
        for (n = 0; n < log->format->ops->nelts; ++n, ++op) {
            p = op->getdata(s, p, op);
        }

        ngx_linefeed(p);

        ngx_rtmp_log_write(s, log, line, p - line);
    }

    return NGX_OK;
}