#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_4__ {scalar_t__ connection; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
struct TYPE_5__ {int offset; } ;
typedef  TYPE_2__ ngx_rtmp_eval_t ;

/* Variables and functions */

__attribute__((used)) static void
ngx_rtmp_eval_connection_str(void *ctx, ngx_rtmp_eval_t *e, ngx_str_t *ret)
{
    ngx_rtmp_session_t  *s = ctx;

    *ret = *(ngx_str_t *) ((u_char *) s->connection + e->offset);
}