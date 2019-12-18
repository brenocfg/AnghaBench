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
typedef  void* uint32_t ;
struct TYPE_3__ {scalar_t__ zsformat; int /*<<< orphan*/ * target; int /*<<< orphan*/ * zs; int /*<<< orphan*/  format; void* cy; void* cx; } ;
typedef  TYPE_1__ gs_texrender_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RENDER_TARGET ; 
 scalar_t__ GS_ZS_NONE ; 
 int /*<<< orphan*/ * gs_texture_create (void*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gs_zstencil_create (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  gs_zstencil_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool texrender_resetbuffer(gs_texrender_t *texrender, uint32_t cx,
				  uint32_t cy)
{
	if (!texrender)
		return false;

	gs_texture_destroy(texrender->target);
	gs_zstencil_destroy(texrender->zs);

	texrender->target = NULL;
	texrender->zs = NULL;
	texrender->cx = cx;
	texrender->cy = cy;

	texrender->target = gs_texture_create(cx, cy, texrender->format, 1,
					      NULL, GS_RENDER_TARGET);
	if (!texrender->target)
		return false;

	if (texrender->zsformat != GS_ZS_NONE) {
		texrender->zs = gs_zstencil_create(cx, cy, texrender->zsformat);
		if (!texrender->zs) {
			gs_texture_destroy(texrender->target);
			texrender->target = NULL;

			return false;
		}
	}

	return true;
}