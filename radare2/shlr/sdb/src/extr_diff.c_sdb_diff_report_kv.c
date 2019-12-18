#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* member_1; char const* member_2; int member_3; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  cb_user; int /*<<< orphan*/  (* cb ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ SdbDiffCtx ;
typedef  TYPE_2__ SdbDiff ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdb_diff_report_kv(SdbDiffCtx *ctx, const char *k, const char *v, bool add) {
	SdbDiff diff = { ctx->path, k, v, add };
	ctx->cb (&diff, ctx->cb_user);
}