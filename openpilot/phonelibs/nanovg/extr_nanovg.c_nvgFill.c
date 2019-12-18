#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  userPtr; int /*<<< orphan*/  (* renderFill ) (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,float,int /*<<< orphan*/ ,TYPE_6__*,int) ;scalar_t__ edgeAntiAlias; } ;
struct TYPE_23__ {float fringeWidth; int drawCallCount; int /*<<< orphan*/  fillTriCount; TYPE_4__* cache; TYPE_3__ params; } ;
struct TYPE_17__ {int /*<<< orphan*/  a; } ;
struct TYPE_16__ {int /*<<< orphan*/  a; } ;
struct TYPE_22__ {TYPE_2__ outerColor; TYPE_1__ innerColor; } ;
struct TYPE_21__ {int nfill; int nstroke; } ;
struct TYPE_20__ {int /*<<< orphan*/  scissor; int /*<<< orphan*/  alpha; TYPE_7__ fill; } ;
struct TYPE_19__ {int npaths; TYPE_6__* paths; int /*<<< orphan*/  bounds; } ;
typedef  TYPE_5__ NVGstate ;
typedef  TYPE_6__ NVGpath ;
typedef  TYPE_7__ NVGpaint ;
typedef  TYPE_8__ NVGcontext ;

/* Variables and functions */
 int /*<<< orphan*/  NVG_MITER ; 
 int /*<<< orphan*/  nvg__expandFill (TYPE_8__*,float,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  nvg__flattenPaths (TYPE_8__*) ; 
 TYPE_5__* nvg__getState (TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,float,int /*<<< orphan*/ ,TYPE_6__*,int) ; 

void nvgFill(NVGcontext* ctx)
{
	NVGstate* state = nvg__getState(ctx);
	const NVGpath* path;
	NVGpaint fillPaint = state->fill;
	int i;

	nvg__flattenPaths(ctx);
	if (ctx->params.edgeAntiAlias)
		nvg__expandFill(ctx, ctx->fringeWidth, NVG_MITER, 2.4f);
	else
		nvg__expandFill(ctx, 0.0f, NVG_MITER, 2.4f);

	// Apply global alpha
	fillPaint.innerColor.a *= state->alpha;
	fillPaint.outerColor.a *= state->alpha;

	ctx->params.renderFill(ctx->params.userPtr, &fillPaint, &state->scissor, ctx->fringeWidth,
						   ctx->cache->bounds, ctx->cache->paths, ctx->cache->npaths);

	// Count triangles
	for (i = 0; i < ctx->cache->npaths; i++) {
		path = &ctx->cache->paths[i];
		ctx->fillTriCount += path->nfill-2;
		ctx->fillTriCount += path->nstroke-2;
		ctx->drawCallCount += 2;
	}
}