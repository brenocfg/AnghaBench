#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct ctxSearchCB {int /*<<< orphan*/  count; int /*<<< orphan*/  rad; int /*<<< orphan*/  prefix; int /*<<< orphan*/  core; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; int /*<<< orphan*/  keyword_length; } ;
typedef  int /*<<< orphan*/  RSignItem ;
typedef  TYPE_1__ RSearchKeyword ;

/* Variables and functions */
 int /*<<< orphan*/  addFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int searchHitCB(RSignItem *it, RSearchKeyword *kw, ut64 addr, void *user) {
	struct ctxSearchCB *ctx = (struct ctxSearchCB *) user;
	addFlag (ctx->core, it, addr, kw->keyword_length, kw->count, ctx->prefix, ctx->rad);
	ctx->count++;
	return 1;
}