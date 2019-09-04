#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int ngx_uint_t ;
struct TYPE_19__ {scalar_t__ auto_pushed; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_23__ {char* data; int len; } ;
struct TYPE_20__ {TYPE_7__ path; TYPE_7__ recorder; } ;
typedef  TYPE_4__ ngx_rtmp_record_done_t ;
struct TYPE_18__ {char* data; int len; } ;
struct TYPE_17__ {char* data; int len; } ;
struct TYPE_21__ {TYPE_2__ basename; TYPE_2__ filename; TYPE_7__ path; TYPE_1__ dirname; TYPE_7__ recorder; } ;
typedef  TYPE_5__ ngx_rtmp_exec_ctx_t ;
struct TYPE_22__ {int /*<<< orphan*/ * conf; int /*<<< orphan*/  active; } ;
typedef  TYPE_6__ ngx_rtmp_exec_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 size_t NGX_RTMP_EXEC_RECORD_DONE ; 
 int /*<<< orphan*/  next_record_done (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_rtmp_exec_module ; 
 int /*<<< orphan*/  ngx_rtmp_exec_unmanaged (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 TYPE_6__* ngx_rtmp_get_module_app_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_null (TYPE_7__*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_exec_record_done(ngx_rtmp_session_t *s, ngx_rtmp_record_done_t *v)
{
    u_char                     c;
    ngx_uint_t                 ext, dir;
    ngx_rtmp_exec_ctx_t       *ctx;
    ngx_rtmp_exec_app_conf_t  *eacf;

    if (s->auto_pushed) {
        goto next;
    }

    eacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_exec_module);
    if (eacf == NULL || !eacf->active) {
        goto next;
    }

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_exec_module);
    if (ctx == NULL) {
        goto next;
    }

    ctx->recorder = v->recorder;
    ctx->path = v->path;

    ctx->dirname.data = ctx->path.data;
    ctx->dirname.len = 0;

    for (dir = ctx->path.len; dir > 0; dir--) {
        c = ctx->path.data[dir - 1];
        if (c == '/' || c == '\\') {
            ctx->dirname.len = dir - 1;
            break;
        }
    }

    ctx->filename.data = ctx->path.data + dir;
    ctx->filename.len = ctx->path.len - dir;

    ctx->basename = ctx->filename;

    for (ext = ctx->filename.len; ext > 0; ext--) {
        if (ctx->filename.data[ext - 1] == '.') {
            ctx->basename.len = ext - 1;
            break;
        }
    }

    ngx_rtmp_exec_unmanaged(s, &eacf->conf[NGX_RTMP_EXEC_RECORD_DONE],
                            "record_done");

    ngx_str_null(&v->recorder);
    ngx_str_null(&v->path);

next:
    return next_record_done(s, v);
}