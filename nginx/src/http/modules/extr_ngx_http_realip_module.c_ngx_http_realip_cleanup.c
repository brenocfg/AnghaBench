#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  addr_text; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; TYPE_2__* connection; } ;
typedef  TYPE_1__ ngx_http_realip_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/  addr_text; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */

__attribute__((used)) static void
ngx_http_realip_cleanup(void *data)
{
    ngx_http_realip_ctx_t *ctx = data;

    ngx_connection_t  *c;

    c = ctx->connection;

    c->sockaddr = ctx->sockaddr;
    c->socklen = ctx->socklen;
    c->addr_text = ctx->addr_text;
}