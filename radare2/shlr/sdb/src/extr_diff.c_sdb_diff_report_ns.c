#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  cb_user; int /*<<< orphan*/  (* cb ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  path; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SdbNs ;
typedef  TYPE_2__ SdbDiffCtx ;
typedef  TYPE_3__ SdbDiff ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdb_diff_report_ns(SdbDiffCtx *ctx, SdbNs *ns, bool add) {
	SdbDiff diff = { ctx->path, ns->name, NULL, add };
	ctx->cb (&diff, ctx->cb_user);
}