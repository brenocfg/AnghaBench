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
struct vec4 {int /*<<< orphan*/  m; } ;

/* Variables and functions */
 int /*<<< orphan*/  _mm_mul_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_set1_ps (float) ; 
 int /*<<< orphan*/  _mm_setzero_ps () ; 
 float sqrtf (float) ; 
 float vec4_dot (struct vec4 const*,struct vec4 const*) ; 

__attribute__((used)) static inline void vec4_norm(struct vec4 *dst, const struct vec4 *v)
{
	float dot_val = vec4_dot(v, v);
	dst->m = (dot_val > 0.0f)
			 ? _mm_mul_ps(v->m, _mm_set1_ps(1.0f / sqrtf(dot_val)))
			 : _mm_setzero_ps();
}