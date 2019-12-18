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
struct TYPE_4__ {scalar_t__ depth; int flags; int /*<<< orphan*/ * bn; } ;
typedef  TYPE_1__ BN_CTX ;

/* Variables and functions */
 int BN_CTX_NUM ; 
 int BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void BN_CTX_free(BN_CTX *ctx)
	{
	int i;

	if (ctx == NULL) return;
	assert(ctx->depth == 0);

	for (i=0; i < BN_CTX_NUM; i++)
		BN_clear_free(&(ctx->bn[i]));
	if (ctx->flags & BN_FLG_MALLOCED)
		free(ctx);
	}