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
struct vec3 {int dummy; } ;
struct plane {float dist; int /*<<< orphan*/  dir; } ;
struct bounds {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bounds_get_center (struct vec3*,struct bounds const*) ; 
 float vec3_plane_dist (struct vec3*,struct plane const*) ; 
 float vec3or_offset_len (struct bounds const*,int /*<<< orphan*/ *) ; 

float bounds_min_dist(const struct bounds *b, const struct plane *p)
{
	struct vec3 center;
	float vec_len = vec3or_offset_len(b, &p->dir) * 0.5f;
	float center_dist;

	bounds_get_center(&center, b);
	center_dist = vec3_plane_dist(&center, p);

	return p->dist + center_dist - vec_len;
}