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
struct quat {int x; int y; int z; int /*<<< orphan*/  w; } ;

/* Variables and functions */
 float EPSILON ; 
 int /*<<< orphan*/  cosf (float) ; 
 int /*<<< orphan*/  quat_copy (struct quat*,struct quat const*) ; 
 int /*<<< orphan*/  quat_mulf (struct quat*,struct quat*,float) ; 
 float sinf (float) ; 
 float sqrtf (int) ; 

void quat_exp(struct quat *dst, const struct quat *q)
{
	float length = sqrtf(q->x * q->x + q->y * q->y + q->z * q->z);
	float sine = sinf(length);

	quat_copy(dst, q);
	sine = (length > EPSILON) ? (sine / length) : 1.0f;
	quat_mulf(dst, dst, sine);
	dst->w = cosf(length);
}