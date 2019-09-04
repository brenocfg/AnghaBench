#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vbva_buf_ctx {int buffer_overflow; int /*<<< orphan*/ * vbva; int /*<<< orphan*/ * record; } ;
struct gen_pool {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  vbva_inform_host (struct vbva_buf_ctx*,struct gen_pool*,int /*<<< orphan*/ ,int) ; 

void vbva_disable(struct vbva_buf_ctx *vbva_ctx, struct gen_pool *ctx,
		  s32 screen)
{
	vbva_ctx->buffer_overflow = false;
	vbva_ctx->record = NULL;
	vbva_ctx->vbva = NULL;

	vbva_inform_host(vbva_ctx, ctx, screen, false);
}