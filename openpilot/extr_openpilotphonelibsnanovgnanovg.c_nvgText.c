#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {float x0; float y0; float x1; float y1; int /*<<< orphan*/  t1; int /*<<< orphan*/  s1; int /*<<< orphan*/  s0; int /*<<< orphan*/  t0; } ;
struct TYPE_18__ {int prevGlyphIndex; float x; } ;
struct TYPE_17__ {float devicePxRatio; int /*<<< orphan*/  fs; } ;
struct TYPE_16__ {scalar_t__ fontId; float fontSize; float letterSpacing; float fontBlur; int /*<<< orphan*/  xform; int /*<<< orphan*/  textAlign; } ;
typedef  int /*<<< orphan*/  NVGvertex ;
typedef  TYPE_1__ NVGstate ;
typedef  TYPE_2__ NVGcontext ;
typedef  TYPE_3__ FONStextIter ;
typedef  TYPE_4__ FONSquad ;

/* Variables and functions */
 scalar_t__ FONS_INVALID ; 
 int /*<<< orphan*/  fonsSetAlign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fonsSetBlur (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsSetFont (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fonsSetSize (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsSetSpacing (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fonsTextIterInit (int /*<<< orphan*/ ,TYPE_3__*,float,float,char const*,char const*) ; 
 scalar_t__ fonsTextIterNext (int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  nvgTransformPoint (float*,float*,int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/ * nvg__allocTempVerts (TYPE_2__*,int) ; 
 int /*<<< orphan*/  nvg__allocTextAtlas (TYPE_2__*) ; 
 int /*<<< orphan*/  nvg__flushTextTexture (TYPE_2__*) ; 
 float nvg__getFontScale (TYPE_1__*) ; 
 TYPE_1__* nvg__getState (TYPE_2__*) ; 
 int nvg__maxi (int,int) ; 
 int /*<<< orphan*/  nvg__renderText (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvg__vset (int /*<<< orphan*/ *,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

float nvgText(NVGcontext* ctx, float x, float y, const char* string, const char* end)
{
	NVGstate* state = nvg__getState(ctx);
	FONStextIter iter, prevIter;
	FONSquad q;
	NVGvertex* verts;
	float scale = nvg__getFontScale(state) * ctx->devicePxRatio;
	float invscale = 1.0f / scale;
	int cverts = 0;
	int nverts = 0;

	if (end == NULL)
		end = string + strlen(string);

	if (state->fontId == FONS_INVALID) return x;

	fonsSetSize(ctx->fs, state->fontSize*scale);
	fonsSetSpacing(ctx->fs, state->letterSpacing*scale);
	fonsSetBlur(ctx->fs, state->fontBlur*scale);
	fonsSetAlign(ctx->fs, state->textAlign);
	fonsSetFont(ctx->fs, state->fontId);

	cverts = nvg__maxi(2, (int)(end - string)) * 6; // conservative estimate.
	verts = nvg__allocTempVerts(ctx, cverts);
	if (verts == NULL) return x;

	fonsTextIterInit(ctx->fs, &iter, x*scale, y*scale, string, end);
	prevIter = iter;
	while (fonsTextIterNext(ctx->fs, &iter, &q)) {
		float c[4*2];
		if (iter.prevGlyphIndex == -1) { // can not retrieve glyph?
			if (!nvg__allocTextAtlas(ctx))
				break; // no memory :(
			if (nverts != 0) {
				nvg__renderText(ctx, verts, nverts);
				nverts = 0;
			}
			iter = prevIter;
			fonsTextIterNext(ctx->fs, &iter, &q); // try again
			if (iter.prevGlyphIndex == -1) // still can not find glyph?
				break;
		}
		prevIter = iter;
		// Transform corners.
		nvgTransformPoint(&c[0],&c[1], state->xform, q.x0*invscale, q.y0*invscale);
		nvgTransformPoint(&c[2],&c[3], state->xform, q.x1*invscale, q.y0*invscale);
		nvgTransformPoint(&c[4],&c[5], state->xform, q.x1*invscale, q.y1*invscale);
		nvgTransformPoint(&c[6],&c[7], state->xform, q.x0*invscale, q.y1*invscale);
		// Create triangles
		if (nverts+6 <= cverts) {
			nvg__vset(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
			nvg__vset(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
			nvg__vset(&verts[nverts], c[2], c[3], q.s1, q.t0); nverts++;
			nvg__vset(&verts[nverts], c[0], c[1], q.s0, q.t0); nverts++;
			nvg__vset(&verts[nverts], c[6], c[7], q.s0, q.t1); nverts++;
			nvg__vset(&verts[nverts], c[4], c[5], q.s1, q.t1); nverts++;
		}
	}

	// TODO: add back-end bit to do this just once per frame.
	nvg__flushTextTexture(ctx);

	nvg__renderText(ctx, verts, nverts);

	return iter.x;
}