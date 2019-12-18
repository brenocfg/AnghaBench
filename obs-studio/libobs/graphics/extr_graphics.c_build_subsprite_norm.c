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

/* Variables and functions */
 int GS_FLIP_U ; 
 int GS_FLIP_V ; 
 int /*<<< orphan*/  build_sprite (struct gs_vb_data*,float,float,float,float,float,float) ; 

__attribute__((used)) static inline void build_subsprite_norm(struct gs_vb_data *data, float fsub_x,
					float fsub_y, float fsub_cx,
					float fsub_cy, float fcx, float fcy,
					uint32_t flip)
{
	float start_u, end_u;
	float start_v, end_v;

	if ((flip & GS_FLIP_U) == 0) {
		start_u = fsub_x / fcx;
		end_u = (fsub_x + fsub_cx) / fcx;
	} else {
		start_u = (fsub_x + fsub_cx) / fcx;
		end_u = fsub_x / fcx;
	}

	if ((flip & GS_FLIP_V) == 0) {
		start_v = fsub_y / fcy;
		end_v = (fsub_y + fsub_cy) / fcy;
	} else {
		start_v = (fsub_y + fsub_cy) / fcy;
		end_v = fsub_y / fcy;
	}

	build_sprite(data, fsub_cx, fsub_cy, start_u, end_u, start_v, end_v);
}