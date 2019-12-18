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
 int /*<<< orphan*/  _mm_set_ps (float,float,float,float) ; 

__attribute__((used)) static inline void quat_set(struct quat *dst, float x, float y, float z,
			    float w)
{
	dst->m = _mm_set_ps(x, y, z, w);
}