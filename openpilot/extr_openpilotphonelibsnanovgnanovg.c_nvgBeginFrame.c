#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  userPtr; int /*<<< orphan*/  (* renderViewport ) (int /*<<< orphan*/ ,int,int,float) ;} ;
struct TYPE_8__ {scalar_t__ textTriCount; scalar_t__ strokeTriCount; scalar_t__ fillTriCount; scalar_t__ drawCallCount; TYPE_1__ params; scalar_t__ nstates; } ;
typedef  TYPE_2__ NVGcontext ;

/* Variables and functions */
 int /*<<< orphan*/  nvgReset (TYPE_2__*) ; 
 int /*<<< orphan*/  nvgSave (TYPE_2__*) ; 
 int /*<<< orphan*/  nvg__setDevicePixelRatio (TYPE_2__*,float) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,float) ; 

void nvgBeginFrame(NVGcontext* ctx, int windowWidth, int windowHeight, float devicePixelRatio)
{
/*	printf("Tris: draws:%d  fill:%d  stroke:%d  text:%d  TOT:%d\n",
		ctx->drawCallCount, ctx->fillTriCount, ctx->strokeTriCount, ctx->textTriCount,
		ctx->fillTriCount+ctx->strokeTriCount+ctx->textTriCount);*/

	ctx->nstates = 0;
	nvgSave(ctx);
	nvgReset(ctx);

	nvg__setDevicePixelRatio(ctx, devicePixelRatio);

	ctx->params.renderViewport(ctx->params.userPtr, windowWidth, windowHeight, devicePixelRatio);

	ctx->drawCallCount = 0;
	ctx->fillTriCount = 0;
	ctx->strokeTriCount = 0;
	ctx->textTriCount = 0;
}