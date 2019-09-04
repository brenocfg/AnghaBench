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
struct TYPE_8__ {float devicePxRatio; int /*<<< orphan*/  fs; } ;
struct TYPE_7__ {scalar_t__ fontId; float fontSize; float letterSpacing; float fontBlur; int /*<<< orphan*/  textAlign; } ;
typedef  TYPE_1__ NVGstate ;
typedef  TYPE_2__ NVGcontext ;

/* Variables and functions */
 scalar_t__ FONS_INVALID ; 
 int /*<<< orphan*/  fonsLineBounds (int /*<<< orphan*/ ,float,float*,float*) ; 
 int /*<<< orphan*/  fonsSetAlign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fonsSetBlur (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsSetFont (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fonsSetSize (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsSetSpacing (int /*<<< orphan*/ ,float) ; 
 float fonsTextBounds (int /*<<< orphan*/ ,float,float,char const*,char const*,float*) ; 
 float nvg__getFontScale (TYPE_1__*) ; 
 TYPE_1__* nvg__getState (TYPE_2__*) ; 

float nvgTextBounds(NVGcontext* ctx, float x, float y, const char* string, const char* end, float* bounds)
{
	NVGstate* state = nvg__getState(ctx);
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;
	float width;

	if (state->fontId == FONS_INVALID) return 0;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);

	width = fonsTextBounds(ctx->fs, x*scale, y*scale, string, end, bounds);
	if (bounds != NULL) {
		// Use line bounds for height.
		fonsLineBounds(ctx->fs, y*scale, &bounds[1], &bounds[3]);
		bounds[0] *= invscale;
		bounds[1] *= invscale;
		bounds[2] *= invscale;
		bounds[3] *= invscale;
	}
	return width * invscale;
}