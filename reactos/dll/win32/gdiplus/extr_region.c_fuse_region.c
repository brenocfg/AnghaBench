#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  region_element ;
struct TYPE_6__ {int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; } ;
struct TYPE_7__ {TYPE_1__ combine; } ;
struct TYPE_8__ {TYPE_2__ elementdata; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {int num_children; TYPE_3__ node; } ;
typedef  TYPE_4__ GpRegion ;
typedef  int /*<<< orphan*/  CombineMode ;

/* Variables and functions */

__attribute__((used)) static inline void fuse_region(GpRegion* region, region_element* left,
        region_element* right, const CombineMode mode)
{
    region->node.type = mode;
    region->node.elementdata.combine.left = left;
    region->node.elementdata.combine.right = right;
    region->num_children += 2;
}