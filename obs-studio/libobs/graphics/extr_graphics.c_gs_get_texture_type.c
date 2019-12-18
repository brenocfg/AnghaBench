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
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_4__ {int (* device_get_texture_type ) (int /*<<< orphan*/  const*) ;} ;
struct TYPE_5__ {TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;
typedef  enum gs_texture_type { ____Placeholder_gs_texture_type } gs_texture_type ;

/* Variables and functions */
 int GS_TEXTURE_2D ; 
 int /*<<< orphan*/  gs_valid_p (char*,int /*<<< orphan*/  const*) ; 
 int stub1 (int /*<<< orphan*/  const*) ; 
 TYPE_2__* thread_graphics ; 

enum gs_texture_type gs_get_texture_type(const gs_texture_t *texture)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid_p("gs_get_texture_type", texture))
		return GS_TEXTURE_2D;

	return graphics->exports.device_get_texture_type(texture);
}