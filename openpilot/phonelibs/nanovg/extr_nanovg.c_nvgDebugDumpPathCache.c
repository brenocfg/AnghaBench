#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* cache; } ;
struct TYPE_10__ {int nfill; int nstroke; TYPE_3__* stroke; TYPE_2__* fill; } ;
struct TYPE_9__ {double x; double y; } ;
struct TYPE_8__ {double x; double y; } ;
struct TYPE_7__ {int npaths; TYPE_4__* paths; } ;
typedef  TYPE_4__ NVGpath ;
typedef  TYPE_5__ NVGcontext ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,double,...) ; 

void nvgDebugDumpPathCache(NVGcontext* ctx)
{
	const NVGpath* path;
	int i, j;

	printf("Dumping %d cached paths\n", ctx->cache->npaths);
	for (i = 0; i < ctx->cache->npaths; i++) {
		path = &ctx->cache->paths[i];
		printf(" - Path %d\n", i);
		if (path->nfill) {
			printf("   - fill: %d\n", path->nfill);
			for (j = 0; j < path->nfill; j++)
				printf("%f\t%f\n", path->fill[j].x, path->fill[j].y);
		}
		if (path->nstroke) {
			printf("   - stroke: %d\n", path->nstroke);
			for (j = 0; j < path->nstroke; j++)
				printf("%f\t%f\n", path->stroke[j].x, path->stroke[j].y);
		}
	}
}