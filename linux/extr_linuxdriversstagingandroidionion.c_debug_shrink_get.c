#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct shrink_control {scalar_t__ nr_to_scan; int /*<<< orphan*/  gfp_mask; } ;
struct TYPE_2__ {int (* count_objects ) (TYPE_1__*,struct shrink_control*) ;} ;
struct ion_heap {TYPE_1__ shrinker; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_HIGHUSER ; 
 int stub1 (TYPE_1__*,struct shrink_control*) ; 

__attribute__((used)) static int debug_shrink_get(void *data, u64 *val)
{
	struct ion_heap *heap = data;
	struct shrink_control sc;
	int objs;

	sc.gfp_mask = GFP_HIGHUSER;
	sc.nr_to_scan = 0;

	objs = heap->shrinker.count_objects(&heap->shrinker, &sc);
	*val = objs;
	return 0;
}