#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct matrix4 {int dummy; } ;
struct TYPE_2__ {float w; } ;
struct matrix3 {TYPE_1__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix4_from_matrix3 (struct matrix4*,struct matrix3 const*) ; 
 int /*<<< orphan*/  matrix4_inv (struct matrix4*,struct matrix4*) ; 

void matrix3_inv(struct matrix3 *dst, const struct matrix3 *m)
{
	struct matrix4 m4;
	matrix4_from_matrix3(&m4, m);
	matrix4_inv((struct matrix4 *)dst, &m4);
	dst->t.w = 0.0f;
}