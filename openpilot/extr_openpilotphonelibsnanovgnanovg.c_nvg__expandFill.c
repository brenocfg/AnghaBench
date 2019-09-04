#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {float fringeWidth; TYPE_3__* cache; } ;
struct TYPE_18__ {int count; int nbevel; size_t first; int nfill; int nstroke; TYPE_1__* stroke; TYPE_1__* fill; int /*<<< orphan*/  convex; } ;
struct TYPE_17__ {int npaths; TYPE_2__* points; TYPE_4__* paths; } ;
struct TYPE_16__ {int flags; float dy; float dx; float x; float dmx; float y; float dmy; } ;
struct TYPE_15__ {float x; float y; } ;
typedef  TYPE_1__ NVGvertex ;
typedef  TYPE_2__ NVGpoint ;
typedef  TYPE_3__ NVGpathCache ;
typedef  TYPE_4__ NVGpath ;
typedef  TYPE_5__ NVGcontext ;

/* Variables and functions */
 int NVG_PR_INNERBEVEL ; 
 int NVG_PT_BEVEL ; 
 int NVG_PT_LEFT ; 
 TYPE_1__* nvg__allocTempVerts (TYPE_5__*,int) ; 
 TYPE_1__* nvg__bevelJoin (TYPE_1__*,TYPE_2__*,TYPE_2__*,float,float,float,float,float) ; 
 int /*<<< orphan*/  nvg__calculateJoins (TYPE_5__*,float,int,float) ; 
 int /*<<< orphan*/  nvg__vset (TYPE_1__*,float,float,float,int) ; 

__attribute__((used)) static int nvg__expandFill(NVGcontext* ctx, float w, int lineJoin, float miterLimit)
{
	NVGpathCache* cache = ctx->cache;
	NVGvertex* verts;
	NVGvertex* dst;
	int cverts, convex, i, j;
	float aa = ctx->fringeWidth;
	int fringe = w > 0.0f;

	nvg__calculateJoins(ctx, w, lineJoin, miterLimit);

	// Calculate max vertex usage.
	cverts = 0;
	for (i = 0; i < cache->npaths; i++) {
		NVGpath* path = &cache->paths[i];
		cverts += path->count + path->nbevel + 1;
		if (fringe)
			cverts += (path->count + path->nbevel*5 + 1) * 2; // plus one for loop
	}

	verts = nvg__allocTempVerts(ctx, cverts);
	if (verts == NULL) return 0;

	convex = cache->npaths == 1 && cache->paths[0].convex;

	for (i = 0; i < cache->npaths; i++) {
		NVGpath* path = &cache->paths[i];
		NVGpoint* pts = &cache->points[path->first];
		NVGpoint* p0;
		NVGpoint* p1;
		float rw, lw, woff;
		float ru, lu;

		// Calculate shape vertices.
		woff = 0.5f*aa;
		dst = verts;
		path->fill = dst;

		if (fringe) {
			// Looping
			p0 = &pts[path->count-1];
			p1 = &pts[0];
			for (j = 0; j < path->count; ++j) {
				if (p1->flags & NVG_PT_BEVEL) {
					float dlx0 = p0->dy;
					float dly0 = -p0->dx;
					float dlx1 = p1->dy;
					float dly1 = -p1->dx;
					if (p1->flags & NVG_PT_LEFT) {
						float lx = p1->x + p1->dmx * woff;
						float ly = p1->y + p1->dmy * woff;
						nvg__vset(dst, lx, ly, 0.5f,1); dst++;
					} else {
						float lx0 = p1->x + dlx0 * woff;
						float ly0 = p1->y + dly0 * woff;
						float lx1 = p1->x + dlx1 * woff;
						float ly1 = p1->y + dly1 * woff;
						nvg__vset(dst, lx0, ly0, 0.5f,1); dst++;
						nvg__vset(dst, lx1, ly1, 0.5f,1); dst++;
					}
				} else {
					nvg__vset(dst, p1->x + (p1->dmx * woff), p1->y + (p1->dmy * woff), 0.5f,1); dst++;
				}
				p0 = p1++;
			}
		} else {
			for (j = 0; j < path->count; ++j) {
				nvg__vset(dst, pts[j].x, pts[j].y, 0.5f,1);
				dst++;
			}
		}

		path->nfill = (int)(dst - verts);
		verts = dst;

		// Calculate fringe
		if (fringe) {
			lw = w + woff;
			rw = w - woff;
			lu = 0;
			ru = 1;
			dst = verts;
			path->stroke = dst;

			// Create only half a fringe for convex shapes so that
			// the shape can be rendered without stenciling.
			if (convex) {
				lw = woff;	// This should generate the same vertex as fill inset above.
				lu = 0.5f;	// Set outline fade at middle.
			}

			// Looping
			p0 = &pts[path->count-1];
			p1 = &pts[0];

			for (j = 0; j < path->count; ++j) {
				if ((p1->flags & (NVG_PT_BEVEL | NVG_PR_INNERBEVEL)) != 0) {
					dst = nvg__bevelJoin(dst, p0, p1, lw, rw, lu, ru, ctx->fringeWidth);
				} else {
					nvg__vset(dst, p1->x + (p1->dmx * lw), p1->y + (p1->dmy * lw), lu,1); dst++;
					nvg__vset(dst, p1->x - (p1->dmx * rw), p1->y - (p1->dmy * rw), ru,1); dst++;
				}
				p0 = p1++;
			}

			// Loop it
			nvg__vset(dst, verts[0].x, verts[0].y, lu,1); dst++;
			nvg__vset(dst, verts[1].x, verts[1].y, ru,1); dst++;

			path->nstroke = (int)(dst - verts);
			verts = dst;
		} else {
			path->stroke = NULL;
			path->nstroke = 0;
		}
	}

	return 1;
}