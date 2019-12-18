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
struct vec2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_texcoord2v (struct vec2*,int) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  vec2_set (struct vec2*,float,float) ; 

void gs_texcoord(float x, float y, int unit)
{
	struct vec2 v2;

	if (!gs_valid("gs_texcoord"))
		return;

	vec2_set(&v2, x, y);
	gs_texcoord2v(&v2, unit);
}