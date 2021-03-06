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
 int /*<<< orphan*/  _mm_sub_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vec4_sub(struct vec4 *dst, const struct vec4 *v1,
			    const struct vec4 *v2)
{
	dst->m = _mm_sub_ps(v1->m, v2->m);
}