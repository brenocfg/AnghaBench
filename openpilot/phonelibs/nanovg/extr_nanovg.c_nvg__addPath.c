#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* cache; } ;
struct TYPE_8__ {int /*<<< orphan*/  winding; int /*<<< orphan*/  first; } ;
struct TYPE_7__ {int npaths; int cpaths; int /*<<< orphan*/  npoints; TYPE_2__* paths; } ;
typedef  TYPE_2__ NVGpath ;
typedef  TYPE_3__ NVGcontext ;

/* Variables and functions */
 int /*<<< orphan*/  NVG_CCW ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (TYPE_2__*,int) ; 

__attribute__((used)) static void nvg__addPath(NVGcontext* ctx)
{
	NVGpath* path;
	if (ctx->cache->npaths+1 > ctx->cache->cpaths) {
		NVGpath* paths;
		int cpaths = ctx->cache->npaths+1 + ctx->cache->cpaths/2;
		paths = (NVGpath*)realloc(ctx->cache->paths, sizeof(NVGpath)*cpaths);
		if (paths == NULL) return;
		ctx->cache->paths = paths;
		ctx->cache->cpaths = cpaths;
	}
	path = &ctx->cache->paths[ctx->cache->npaths];
	memset(path, 0, sizeof(*path));
	path->first = ctx->cache->npoints;
	path->winding = NVG_CCW;

	ctx->cache->npaths++;
}