#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nnodes; int /*<<< orphan*/ * nodes; } ;
typedef  TYPE_1__ FONSatlas ;

/* Variables and functions */

__attribute__((used)) static void fons__atlasRemoveNode(FONSatlas* atlas, int idx)
{
	int i;
	if (atlas->nnodes == 0) return;
	for (i = idx; i < atlas->nnodes-1; i++)
		atlas->nodes[i] = atlas->nodes[i+1];
	atlas->nnodes--;
}