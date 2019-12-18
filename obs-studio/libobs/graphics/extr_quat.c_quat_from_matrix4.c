#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct quat {float w; float x; float y; float z; float* ptr; } ;
struct TYPE_6__ {float z; float y; float x; } ;
struct TYPE_5__ {float y; float z; float x; } ;
struct TYPE_4__ {float x; float z; float y; } ;
struct matrix4 {TYPE_3__ z; TYPE_2__ y; TYPE_1__ x; } ;
struct f4x4 {float** ptr; } ;

/* Variables and functions */
 float sqrtf (float) ; 

void quat_from_matrix4(struct quat *dst, const struct matrix4 *m)
{
	float tr = (m->x.x + m->y.y + m->z.z);
	float inv_half;
	float four_d;
	int i, j, k;

	if (tr > 0.0f) {
		four_d = sqrtf(tr + 1.0f);
		dst->w = four_d * 0.5f;

		inv_half = 0.5f / four_d;
		dst->x = (m->y.z - m->z.y) * inv_half;
		dst->y = (m->z.x - m->x.z) * inv_half;
		dst->z = (m->x.y - m->y.x) * inv_half;
	} else {
		struct f4x4 *val = (struct f4x4 *)m;

		i = (m->x.x > m->y.y) ? 0 : 1;

		if (m->z.z > val->ptr[i][i])
			i = 2;

		j = (i + 1) % 3;
		k = (i + 2) % 3;

		/* ---------------------------------- */

		four_d = sqrtf(
			(val->ptr[i][i] - val->ptr[j][j] - val->ptr[k][k]) +
			1.0f);

		dst->ptr[i] = four_d * 0.5f;

		inv_half = 0.5f / four_d;
		dst->ptr[j] = (val->ptr[i][j] + val->ptr[j][i]) * inv_half;
		dst->ptr[k] = (val->ptr[i][k] + val->ptr[k][i]) * inv_half;
		dst->w = (val->ptr[j][k] - val->ptr[k][j]) * inv_half;
	}
}