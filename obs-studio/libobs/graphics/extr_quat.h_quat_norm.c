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
struct quat {int /*<<< orphan*/  m; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set1_ps (float) ; 
 int /*<<< orphan*/  _mm_setzero_ps () ; 
 float quat_dot (struct quat const*,struct quat const*) ; 
 float sqrtf (float) ; 

__attribute__((used)) static inline void quat_norm(struct quat *dst, const struct quat *q)
{
	float dot_val = quat_dot(q, q);
	dst->m = (dot_val > 0.0f)
			 ? _mm_mul_ps(q->m, _mm_set1_ps(1.0f / sqrtf(dot_val)))
			 : _mm_setzero_ps();
}