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
struct TYPE_5__ {int width; int height; scalar_t__ nnodes; TYPE_1__* nodes; } ;
struct TYPE_4__ {short width; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_2__ FONSatlas ;

/* Variables and functions */

__attribute__((used)) static void fons__atlasReset(FONSatlas* atlas, int w, int h)
{
	atlas->width = w;
	atlas->height = h;
	atlas->nnodes = 0;

	// Init root node.
	atlas->nodes[0].x = 0;
	atlas->nodes[0].y = 0;
	atlas->nodes[0].width = (short)w;
	atlas->nnodes++;
}