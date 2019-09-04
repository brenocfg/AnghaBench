#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  nnodes; } ;
typedef  TYPE_1__ FONSatlas ;

/* Variables and functions */
 int /*<<< orphan*/  fons__atlasInsertNode (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fons__atlasExpand(FONSatlas* atlas, int w, int h)
{
	// Insert node for empty space
	if (w > atlas->width)
		fons__atlasInsertNode(atlas, atlas->nnodes, atlas->width, 0, w - atlas->width);
	atlas->width = w;
	atlas->height = h;
}