#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_6__ {int failed; TYPE_3__* conf; } ;
typedef  TYPE_2__ ngx_rtmp_record_rec_ctx_t ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_7__ {TYPE_1__ id; int /*<<< orphan*/  notify; } ;
typedef  TYPE_3__ ngx_rtmp_record_app_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_rtmp_send_status (int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static void
ngx_rtmp_record_notify_error(ngx_rtmp_session_t *s,
                             ngx_rtmp_record_rec_ctx_t *rctx)
{
    ngx_rtmp_record_app_conf_t *rracf = rctx->conf;

    rctx->failed = 1;

    if (!rracf->notify) {
        return;
    }

    ngx_rtmp_send_status(s, "NetStream.Record.Failed", "error",
                         rracf->id.data ? (char *) rracf->id.data : "");
}