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

/* Variables and functions */
 int /*<<< orphan*/  gs_normal3v (struct vec3*) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  vec3_set (struct vec3*,float,float,float) ; 

void gs_normal3f(float x, float y, float z)
{
	struct vec3 v3;

	if (!gs_valid("gs_normal3f"))
		return;

	vec3_set(&v3, x, y, z);
	gs_normal3v(&v3);
}