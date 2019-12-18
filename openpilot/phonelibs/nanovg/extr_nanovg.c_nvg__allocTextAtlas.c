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
struct TYPE_6__ {scalar_t__ (* renderCreateTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  userPtr; } ;
struct TYPE_7__ {int fontImageIdx; scalar_t__* fontImages; int /*<<< orphan*/  fs; TYPE_1__ params; } ;
typedef  TYPE_2__ NVGcontext ;

/* Variables and functions */
 int NVG_MAX_FONTIMAGES ; 
 int NVG_MAX_FONTIMAGE_SIZE ; 
 int /*<<< orphan*/  NVG_TEXTURE_ALPHA ; 
 int /*<<< orphan*/  fonsResetAtlas (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvgImageSize (TYPE_2__*,scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  nvg__flushTextTexture (TYPE_2__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvg__allocTextAtlas(NVGcontext* ctx)
{
	int iw, ih;
	nvg__flushTextTexture(ctx);
	if (ctx->fontImageIdx >= NVG_MAX_FONTIMAGES-1)
		return 0;
	// if next fontImage already have a texture
	if (ctx->fontImages[ctx->fontImageIdx+1] != 0)
		nvgImageSize(ctx, ctx->fontImages[ctx->fontImageIdx+1], &iw, &ih);
	else { // calculate the new font image size and create it.
		nvgImageSize(ctx, ctx->fontImages[ctx->fontImageIdx], &iw, &ih);
		if (iw > ih)
			ih *= 2;
		else
			iw *= 2;
		if (iw > NVG_MAX_FONTIMAGE_SIZE || ih > NVG_MAX_FONTIMAGE_SIZE)
			iw = ih = NVG_MAX_FONTIMAGE_SIZE;
		ctx->fontImages[ctx->fontImageIdx+1] = ctx->params.renderCreateTexture(ctx->params.userPtr, NVG_TEXTURE_ALPHA, iw, ih, 0, NULL);
	}
	++ctx->fontImageIdx;
	fonsResetAtlas(ctx->fs, iw, ih);
	return 1;
}