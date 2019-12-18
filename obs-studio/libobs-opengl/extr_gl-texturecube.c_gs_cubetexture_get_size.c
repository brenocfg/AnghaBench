#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct gs_texture_cube {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_texture_cube (int /*<<< orphan*/  const*,char*) ; 

uint32_t gs_cubetexture_get_size(const gs_texture_t *cubetex)
{
	const struct gs_texture_cube *cube =
		(const struct gs_texture_cube *)cubetex;

	if (!is_texture_cube(cubetex, "gs_cubetexture_get_size"))
		return 0;

	return cube->size;
}