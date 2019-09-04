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
struct TYPE_4__ {int /*<<< orphan*/  zs; int /*<<< orphan*/  target; } ;
typedef  TYPE_1__ gs_texrender_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_zstencil_destroy (int /*<<< orphan*/ ) ; 

void gs_texrender_destroy(gs_texrender_t *texrender)
{
	if (texrender) {
		gs_texture_destroy(texrender->target);
		gs_zstencil_destroy(texrender->zs);
		bfree(texrender);
	}
}