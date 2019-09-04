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
typedef  int /*<<< orphan*/  u64 ;
struct send_ctx {int /*<<< orphan*/  deleted_refs; int /*<<< orphan*/  parent_root; } ;
struct fs_path {int dummy; } ;

/* Variables and functions */
 int record_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __record_deleted_ref(int num, u64 dir, int index,
				struct fs_path *name,
				void *ctx)
{
	struct send_ctx *sctx = ctx;
	return record_ref(sctx->parent_root, dir, name, ctx,
			  &sctx->deleted_refs);
}