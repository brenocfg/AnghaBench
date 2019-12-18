#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ depth; int /*<<< orphan*/ * pos; int /*<<< orphan*/  tos; scalar_t__ too_many; } ;
typedef  TYPE_1__ BN_CTX ;

/* Variables and functions */
 scalar_t__ BN_CTX_NUM_POS ; 
 int /*<<< orphan*/  BN_CTX_start (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

void BN_CTX_end(BN_CTX *ctx)
	{
	if (ctx == NULL) return;
	assert(ctx->depth > 0);
	if (ctx->depth == 0)
		/* should never happen, but we can tolerate it if not in
		 * debug mode (could be a 'goto err' in the calling function
		 * before BN_CTX_start was reached) */
		BN_CTX_start(ctx);

	ctx->too_many = 0;
	ctx->depth--;
	if (ctx->depth < BN_CTX_NUM_POS)
		ctx->tos = ctx->pos[ctx->depth];
	}