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
 int /*<<< orphan*/  fonsSetAlign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fonsSetBlur (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsSetFont (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fonsSetSize (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsSetSpacing (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsVertMetrics (int /*<<< orphan*/ ,float*,float*,float*) ; 
 float nvg__getFontScale (TYPE_1__*) ; 
 TYPE_1__* nvg__getState (TYPE_2__*) ; 

void nvgTextMetrics(NVGcontext* ctx, float* ascender, float* descender, float* lineh)
{
	NVGstate* state = nvg__getState(ctx);
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;

	if (state->fontId == FONS_INVALID) return;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);

	fonsVertMetrics(ctx->fs, ascender, descender, lineh);
	if (ascender != NULL)
		*ascender *= invscale;
	if (descender != NULL)
		*descender *= invscale;
	if (lineh != NULL)
		*lineh *= invscale;
}