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
struct vec3 {int /*<<< orphan*/  m; } ;
typedef  int /*<<< orphan*/  __m128 ;

/* Variables and functions */
 int /*<<< orphan*/  _MM_SHUFFLE (int,int,int,int) ; 
 int /*<<< orphan*/  _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_shuffle_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_sub_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vec3_cross(struct vec3 *dst, const struct vec3 *v1,
			      const struct vec3 *v2)
{
	__m128 s1v1 = _mm_shuffle_ps(v1->m, v1->m, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 s1v2 = _mm_shuffle_ps(v2->m, v2->m, _MM_SHUFFLE(3, 1, 0, 2));
	__m128 s2v1 = _mm_shuffle_ps(v1->m, v1->m, _MM_SHUFFLE(3, 1, 0, 2));
	__m128 s2v2 = _mm_shuffle_ps(v2->m, v2->m, _MM_SHUFFLE(3, 0, 2, 1));
	dst->m = _mm_sub_ps(_mm_mul_ps(s1v1, s1v2), _mm_mul_ps(s2v1, s2v2));
}