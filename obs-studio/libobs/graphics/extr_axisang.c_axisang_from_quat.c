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
struct quat {float x; float y; float z; int /*<<< orphan*/  w; } ;
struct axisang {float x; float y; float z; float w; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPSILON ; 
 float acosf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_float (float,float,int /*<<< orphan*/ ) ; 
 float sqrtf (float) ; 

void axisang_from_quat(struct axisang *dst, const struct quat *q)
{
	float len, leni;

	len = q->x * q->x + q->y * q->y + q->z * q->z;
	if (!close_float(len, 0.0f, EPSILON)) {
		leni = 1.0f / sqrtf(len);
		dst->x = q->x * leni;
		dst->y = q->y * leni;
		dst->z = q->z * leni;
		dst->w = acosf(q->w) * 2.0f;
	} else {
		dst->x = 0.0f;
		dst->y = 0.0f;
		dst->z = 0.0f;
		dst->w = 0.0f;
	}
}