#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  userPtr; int /*<<< orphan*/  (* renderUpdateTexture ) (int /*<<< orphan*/ ,int,int,int,int,int,unsigned char const*) ;} ;
struct TYPE_5__ {int* fontImages; size_t fontImageIdx; TYPE_1__ params; int /*<<< orphan*/  fs; } ;
typedef  TYPE_2__ NVGcontext ;

/* Variables and functions */
 unsigned char* fonsGetTextureData (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ fonsValidateTexture (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int,int,int,unsigned char const*) ; 

__attribute__((used)) static void nvg__flushTextTexture(NVGcontext* ctx)
{
	int dirty[4];

	if (fonsValidateTexture(ctx->fs, dirty)) {
		int fontImage = ctx->fontImages[ctx->fontImageIdx];
		// Update texture
		if (fontImage != 0) {
			int iw, ih;
			const unsigned char* data = fonsGetTextureData(ctx->fs, &iw, &ih);
			int x = dirty[0];
			int y = dirty[1];
			int w = dirty[2] - dirty[0];
			int h = dirty[3] - dirty[1];
			ctx->params.renderUpdateTexture(ctx->params.userPtr, fontImage, x,y, w,h, data);
		}
	}
}