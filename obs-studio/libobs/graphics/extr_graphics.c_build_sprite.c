#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vec2 {int dummy; } ;
struct gs_vb_data {scalar_t__ points; TYPE_1__* tvarray; } ;
struct TYPE_2__ {struct vec2* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec2_set (struct vec2*,float,float) ; 
 int /*<<< orphan*/  vec3_set (scalar_t__,float,float,float) ; 
 int /*<<< orphan*/  vec3_zero (scalar_t__) ; 

__attribute__((used)) static void build_sprite(struct gs_vb_data *data, float fcx, float fcy,
			 float start_u, float end_u, float start_v, float end_v)
{
	struct vec2 *tvarray = data->tvarray[0].array;

	vec3_zero(data->points);
	vec3_set(data->points + 1, fcx, 0.0f, 0.0f);
	vec3_set(data->points + 2, 0.0f, fcy, 0.0f);
	vec3_set(data->points + 3, fcx, fcy, 0.0f);
	vec2_set(tvarray, start_u, start_v);
	vec2_set(tvarray + 1, end_u, start_v);
	vec2_set(tvarray + 2, start_u, end_v);
	vec2_set(tvarray + 3, end_u, end_v);
}