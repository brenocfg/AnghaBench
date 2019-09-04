#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ctxFcnMatchCB {scalar_t__ mincc; int (* cb ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  user; int /*<<< orphan*/  fcn; } ;
struct TYPE_7__ {scalar_t__ cc; } ;
struct TYPE_6__ {TYPE_2__* graph; } ;
typedef  TYPE_1__ RSignItem ;
typedef  TYPE_2__ RSignGraph ;

/* Variables and functions */
 int /*<<< orphan*/  fcnMetricsCmp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int graphMatchCB(RSignItem *it, void *user) {
	struct ctxFcnMatchCB *ctx = (struct ctxFcnMatchCB *) user;
	RSignGraph *graph = it->graph;

	if (!graph) {
		return 1;
	}

	if (graph->cc < ctx->mincc) {
		return 1;
	}

	if (!fcnMetricsCmp (it, ctx->fcn)) {
		return 1;
	}

	if (ctx->cb) {
		return ctx->cb (it, ctx->fcn, ctx->user);
	}

	return 1;
}