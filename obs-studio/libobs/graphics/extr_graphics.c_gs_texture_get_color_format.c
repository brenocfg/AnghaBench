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
struct TYPE_4__ {int (* gs_texture_get_color_format ) (int /*<<< orphan*/  const*) ;} ;
struct TYPE_5__ {TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;

/* Variables and functions */
 int GS_UNKNOWN ; 
 int /*<<< orphan*/  gs_valid_p (char*,int /*<<< orphan*/  const*) ; 
 int stub1 (int /*<<< orphan*/  const*) ; 
 TYPE_2__* thread_graphics ; 

enum gs_color_format gs_texture_get_color_format(const gs_texture_t *tex)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid_p("gs_texture_get_color_format", tex))
		return GS_UNKNOWN;

	return graphics->exports.gs_texture_get_color_format(tex);
}