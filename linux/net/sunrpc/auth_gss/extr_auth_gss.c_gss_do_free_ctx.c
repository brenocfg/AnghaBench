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
struct TYPE_4__ {struct gss_cl_ctx* data; } ;
struct TYPE_3__ {struct gss_cl_ctx* data; } ;
struct gss_cl_ctx {TYPE_2__ gc_acceptor; TYPE_1__ gc_wire_ctx; int /*<<< orphan*/  gc_gss_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  gss_delete_sec_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gss_cl_ctx*) ; 

__attribute__((used)) static void
gss_do_free_ctx(struct gss_cl_ctx *ctx)
{
	gss_delete_sec_context(&ctx->gc_gss_ctx);
	kfree(ctx->gc_wire_ctx.data);
	kfree(ctx->gc_acceptor.data);
	kfree(ctx);
}