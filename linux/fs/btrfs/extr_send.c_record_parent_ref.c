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
typedef  int /*<<< orphan*/  u64 ;
struct parent_paths_ctx {int /*<<< orphan*/  refs; TYPE_1__* sctx; } ;
struct fs_path {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent_root; } ;

/* Variables and functions */
 int record_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int record_parent_ref(int num, u64 dir, int index, struct fs_path *name,
			     void *ctx)
{
	struct parent_paths_ctx *ppctx = ctx;

	return record_ref(ppctx->sctx->parent_root, dir, name, ppctx->sctx,
			  ppctx->refs);
}