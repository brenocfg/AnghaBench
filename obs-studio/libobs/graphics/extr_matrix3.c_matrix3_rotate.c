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
struct matrix3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix3_from_quat (struct matrix3*,struct quat const*) ; 
 int /*<<< orphan*/  matrix3_mul (struct matrix3*,struct matrix3 const*,struct matrix3*) ; 

void matrix3_rotate(struct matrix3 *dst, const struct matrix3 *m,
		    const struct quat *q)
{
	struct matrix3 temp;
	matrix3_from_quat(&temp, q);
	matrix3_mul(dst, m, &temp);
}