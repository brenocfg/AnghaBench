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
struct matrix3 {int dummy; } ;
struct axisang {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  axisang_set (struct axisang*,float,float,float,float) ; 
 int /*<<< orphan*/  matrix3_rotate_aa (struct matrix3*,struct matrix3 const*,struct axisang*) ; 

__attribute__((used)) static inline void matrix3_rotate_aa4f(struct matrix3 *dst,
				       const struct matrix3 *m, float x,
				       float y, float z, float rot)
{
	struct axisang aa;
	axisang_set(&aa, x, y, z, rot);
	matrix3_rotate_aa(dst, m, &aa);
}