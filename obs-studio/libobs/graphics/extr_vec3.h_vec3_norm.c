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

/* Variables and functions */
 int /*<<< orphan*/  _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set1_ps (float) ; 
 int /*<<< orphan*/  _mm_setzero_ps () ; 
 float sqrtf (float) ; 
 float vec3_dot (struct vec3 const*,struct vec3 const*) ; 

__attribute__((used)) static inline void vec3_norm(struct vec3 *dst, const struct vec3 *v)
{
	float dot_val = vec3_dot(v, v);
	dst->m = (dot_val > 0.0f)
			 ? _mm_mul_ps(v->m, _mm_set1_ps(1.0f / sqrtf(dot_val)))
			 : _mm_setzero_ps();
}