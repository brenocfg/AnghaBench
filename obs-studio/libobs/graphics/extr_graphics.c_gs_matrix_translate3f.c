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
struct matrix4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  matrix4_translate3v_i (struct matrix4*,struct vec3*,struct matrix4*) ; 
 int /*<<< orphan*/  thread_graphics ; 
 struct matrix4* top_matrix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec3_set (struct vec3*,float,float,float) ; 

void gs_matrix_translate3f(float x, float y, float z)
{
	struct matrix4 *top_mat;
	struct vec3 p;

	if (!gs_valid("gs_matrix_translate3f"))
		return;

	top_mat = top_matrix(thread_graphics);
	if (top_mat) {
		vec3_set(&p, x, y, z);
		matrix4_translate3v_i(top_mat, &p, top_mat);
	}
}