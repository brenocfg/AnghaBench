#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float w; int /*<<< orphan*/  m; } ;
struct TYPE_16__ {int /*<<< orphan*/  m; } ;
struct TYPE_14__ {int /*<<< orphan*/  m; } ;
struct TYPE_12__ {int /*<<< orphan*/  m; } ;
struct matrix4 {TYPE_3__ t; TYPE_8__ z; TYPE_6__ y; TYPE_4__ x; } ;
struct TYPE_10__ {int /*<<< orphan*/  m; } ;
struct TYPE_9__ {int /*<<< orphan*/  m; } ;
struct TYPE_15__ {int /*<<< orphan*/  m; } ;
struct TYPE_13__ {int /*<<< orphan*/  m; } ;
struct matrix3 {TYPE_2__ t; TYPE_1__ z; TYPE_7__ y; TYPE_5__ x; } ;

/* Variables and functions */

void matrix4_from_matrix3(struct matrix4 *dst, const struct matrix3 *m)
{
	dst->x.m = m->x.m;
	dst->y.m = m->y.m;
	dst->z.m = m->z.m;
	dst->t.m = m->t.m;
	dst->t.w = 1.0f;
}