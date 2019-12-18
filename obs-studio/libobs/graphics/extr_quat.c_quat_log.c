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
struct quat {float w; } ;

/* Variables and functions */
 float EPSILON ; 
 float acosf (float) ; 
 float fabsf (float) ; 
 int /*<<< orphan*/  quat_copy (struct quat*,struct quat const*) ; 
 int /*<<< orphan*/  quat_mulf (struct quat*,struct quat*,float) ; 
 float sinf (float) ; 

void quat_log(struct quat *dst, const struct quat *q)
{
	float angle = acosf(q->w);
	float sine = sinf(angle);
	float w = q->w;

	quat_copy(dst, q);
	dst->w = 0.0f;

	if ((fabsf(w) < 1.0f) && (fabsf(sine) >= EPSILON)) {
		sine = angle / sine;
		quat_mulf(dst, dst, sine);
	}
}