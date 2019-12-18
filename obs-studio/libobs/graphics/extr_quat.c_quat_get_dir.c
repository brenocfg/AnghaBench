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
struct quat {int dummy; } ;
struct matrix3 {int /*<<< orphan*/  z; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix3_from_quat (struct matrix3*,struct quat const*) ; 
 int /*<<< orphan*/  vec3_copy (struct vec3*,int /*<<< orphan*/ *) ; 

void quat_get_dir(struct vec3 *dst, const struct quat *q)
{
	struct matrix3 m;
	matrix3_from_quat(&m, q);
	vec3_copy(dst, &m.z);
}