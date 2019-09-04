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
struct matrix4 {int dummy; } ;
struct axisang {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  axisang_set (struct axisang*,float,float,float,float) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  matrix4_rotate_aa_i (struct matrix4*,struct axisang*,struct matrix4*) ; 
 int /*<<< orphan*/  thread_graphics ; 
 struct matrix4* top_matrix (int /*<<< orphan*/ ) ; 

void gs_matrix_rotaa4f(float x, float y, float z, float angle)
{
	struct matrix4 *top_mat;
	struct axisang aa;

	if (!gs_valid("gs_matrix_rotaa4f"))
		return;

	top_mat = top_matrix(thread_graphics);
	if (top_mat) {
		axisang_set(&aa, x, y, z, angle);
		matrix4_rotate_aa_i(top_mat, &aa, top_mat);
	}
}