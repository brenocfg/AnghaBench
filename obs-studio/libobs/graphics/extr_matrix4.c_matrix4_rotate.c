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
struct quat {int dummy; } ;
struct matrix4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix4_from_quat (struct matrix4*,struct quat const*) ; 
 int /*<<< orphan*/  matrix4_mul (struct matrix4*,struct matrix4 const*,struct matrix4*) ; 

void matrix4_rotate(struct matrix4 *dst, const struct matrix4 *m,
		    const struct quat *q)
{
	struct matrix4 temp;
	matrix4_from_quat(&temp, q);
	matrix4_mul(dst, m, &temp);
}