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
typedef  int uint32_t ;
struct gs_vb_data {int dummy; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 int GS_FLIP_U ; 
 int GS_FLIP_V ; 
 int /*<<< orphan*/  assign_sprite_rect (float*,float*,float,int) ; 
 int /*<<< orphan*/  build_sprite (struct gs_vb_data*,float,float,float,float,float,float) ; 
 scalar_t__ gs_texture_get_height (int /*<<< orphan*/ *) ; 
 scalar_t__ gs_texture_get_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void build_sprite_rect(struct gs_vb_data *data, gs_texture_t *tex,
				     float fcx, float fcy, uint32_t flip)
{
	float start_u, end_u;
	float start_v, end_v;
	float width = (float)gs_texture_get_width(tex);
	float height = (float)gs_texture_get_height(tex);

	assign_sprite_rect(&start_u, &end_u, width, (flip & GS_FLIP_U) != 0);
	assign_sprite_rect(&start_v, &end_v, height, (flip & GS_FLIP_V) != 0);
	build_sprite(data, fcx, fcy, start_u, end_u, start_v, end_v);
}