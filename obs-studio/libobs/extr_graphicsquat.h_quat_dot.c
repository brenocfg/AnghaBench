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
struct vec3 {float x; void* m; } ;
struct quat {int /*<<< orphan*/  m; } ;
typedef  void* __m128 ;

/* Variables and functions */
 void* _mm_add_ps (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  _mm_movehl_ps (void*,void*) ; 
 void* _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_shuffle_ps (void*,void*,int) ; 

__attribute__((used)) static inline float quat_dot(const struct quat *q1, const struct quat *q2)
{
	struct vec3 add;
	__m128 mul = _mm_mul_ps(q1->m, q2->m);
	add.m = _mm_add_ps(_mm_movehl_ps(mul, mul), mul);
	add.m = _mm_add_ps(_mm_shuffle_ps(add.m, add.m, 0x55), add.m);
	return add.x;
}