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
struct vec3 {int /*<<< orphan*/  y; int /*<<< orphan*/  z; int /*<<< orphan*/  x; } ;
struct quat {int dummy; } ;
struct axisang {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPSILON ; 
 int /*<<< orphan*/  asinf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atan2f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axisang_set (struct axisang*,float,float,float,int /*<<< orphan*/ ) ; 
 int close_float (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quat_copy (struct quat*,struct quat*) ; 
 int /*<<< orphan*/  quat_from_axisang (struct quat*,struct axisang*) ; 
 int /*<<< orphan*/  quat_identity (struct quat*) ; 
 int /*<<< orphan*/  quat_mul (struct quat*,struct quat*,struct quat*) ; 
 int /*<<< orphan*/  vec3_neg (struct vec3*,struct vec3*) ; 
 int /*<<< orphan*/  vec3_norm (struct vec3*,struct vec3 const*) ; 

void quat_set_look_dir(struct quat *dst, const struct vec3 *dir)
{
	struct vec3 new_dir;
	struct quat xz_rot, yz_rot;
	bool xz_valid;
	bool yz_valid;
	struct axisang aa;

	vec3_norm(&new_dir, dir);
	vec3_neg(&new_dir, &new_dir);

	quat_identity(&xz_rot);
	quat_identity(&yz_rot);

	xz_valid = close_float(new_dir.x, 0.0f, EPSILON) ||
		   close_float(new_dir.z, 0.0f, EPSILON);
	yz_valid = close_float(new_dir.y, 0.0f, EPSILON);

	if (xz_valid) {
		axisang_set(&aa, 0.0f, 1.0f, 0.0f,
			    atan2f(new_dir.x, new_dir.z));

		quat_from_axisang(&xz_rot, &aa);
	}
	if (yz_valid) {
		axisang_set(&aa, -1.0f, 0.0f, 0.0f, asinf(new_dir.y));
		quat_from_axisang(&yz_rot, &aa);
	}

	if (!xz_valid)
		quat_copy(dst, &yz_rot);
	else if (!yz_valid)
		quat_copy(dst, &xz_rot);
	else
		quat_mul(dst, &xz_rot, &yz_rot);
}