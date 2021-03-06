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
struct matrix4 {int dummy; } ;
struct axisang {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix4_from_axisang (struct matrix4*,struct axisang const*) ; 
 int /*<<< orphan*/  matrix4_mul (struct matrix4*,struct matrix4*,struct matrix4 const*) ; 

void matrix4_rotate_aa_i(struct matrix4 *dst, const struct axisang *aa,
			 const struct matrix4 *m)
{
	struct matrix4 temp;
	matrix4_from_axisang(&temp, aa);
	matrix4_mul(dst, &temp, m);
}