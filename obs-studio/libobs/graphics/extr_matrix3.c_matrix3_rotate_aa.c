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
 int /*<<< orphan*/  matrix3_from_axisang (struct matrix3*,struct axisang const*) ; 
 int /*<<< orphan*/  matrix3_mul (struct matrix3*,struct matrix3 const*,struct matrix3*) ; 

void matrix3_rotate_aa(struct matrix3 *dst, const struct matrix3 *m,
		       const struct axisang *aa)
{
	struct matrix3 temp;
	matrix3_from_axisang(&temp, aa);
	matrix3_mul(dst, m, &temp);
}