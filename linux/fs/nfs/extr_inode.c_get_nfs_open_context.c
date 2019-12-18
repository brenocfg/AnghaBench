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
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct nfs_open_context {TYPE_1__ lock_context; } ;

/* Variables and functions */
 scalar_t__ refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

struct nfs_open_context *get_nfs_open_context(struct nfs_open_context *ctx)
{
	if (ctx != NULL && refcount_inc_not_zero(&ctx->lock_context.count))
		return ctx;
	return NULL;
}