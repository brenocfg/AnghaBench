#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ relay; scalar_t__ auto_pushed; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
struct TYPE_11__ {int /*<<< orphan*/  args; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ngx_rtmp_publish_t ;
struct TYPE_12__ {int publish; } ;
typedef  TYPE_3__ ngx_rtmp_log_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  next_publish (TYPE_1__*,TYPE_2__*) ; 
 TYPE_3__* ngx_rtmp_log_set_names (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_log_publish(ngx_rtmp_session_t *s, ngx_rtmp_publish_t *v)
{
    ngx_rtmp_log_ctx_t *ctx;

    if (s->auto_pushed || s->relay) {
        goto next;
    }

    ctx = ngx_rtmp_log_set_names(s, v->name, v->args);
    if (ctx == NULL) {
        goto next;
    }

    ctx->publish = 1;

next:
    return next_publish(s, v);
}