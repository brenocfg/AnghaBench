#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  userPtr; int /*<<< orphan*/  (* renderTriangles ) (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_16__ {size_t fontImageIdx; int textTriCount; int /*<<< orphan*/  drawCallCount; TYPE_3__ params; int /*<<< orphan*/ * fontImages; } ;
struct TYPE_12__ {int /*<<< orphan*/  a; } ;
struct TYPE_11__ {int /*<<< orphan*/  a; } ;
struct TYPE_15__ {TYPE_2__ outerColor; TYPE_1__ innerColor; int /*<<< orphan*/  image; } ;
struct TYPE_14__ {int /*<<< orphan*/  scissor; int /*<<< orphan*/  alpha; TYPE_5__ fill; } ;
typedef  int /*<<< orphan*/  NVGvertex ;
typedef  TYPE_4__ NVGstate ;
typedef  TYPE_5__ NVGpaint ;
typedef  TYPE_6__ NVGcontext ;

/* Variables and functions */
 TYPE_4__* nvg__getState (TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void nvg__renderText(NVGcontext* ctx, NVGvertex* verts, int nverts)
{
	NVGstate* state = nvg__getState(ctx);
	NVGpaint paint = state->fill;

	// Render triangles.
	paint.image = ctx->fontImages[ctx->fontImageIdx];

	// Apply global alpha
	paint.innerColor.a *= state->alpha;
	paint.outerColor.a *= state->alpha;

	ctx->params.renderTriangles(ctx->params.userPtr, &paint, &state->scissor, verts, nverts);

	ctx->drawCallCount++;
	ctx->textTriCount += nverts/3;
}