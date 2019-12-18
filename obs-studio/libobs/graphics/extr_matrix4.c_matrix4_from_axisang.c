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
struct axisang {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix4_from_quat (struct matrix4*,struct quat*) ; 
 int /*<<< orphan*/  quat_from_axisang (struct quat*,struct axisang const*) ; 

void matrix4_from_axisang(struct matrix4 *dst, const struct axisang *aa)
{
	struct quat q;
	quat_from_axisang(&q, aa);
	matrix4_from_quat(dst, &q);
}