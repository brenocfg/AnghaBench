#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nft_ctx {TYPE_1__* table; } ;
struct TYPE_2__ {scalar_t__ use; struct TYPE_2__* name; int /*<<< orphan*/  chains_ht; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  rhltable_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nf_tables_table_destroy(struct nft_ctx *ctx)
{
	if (WARN_ON(ctx->table->use > 0))
		return;

	rhltable_destroy(&ctx->table->chains_ht);
	kfree(ctx->table->name);
	kfree(ctx->table);
}