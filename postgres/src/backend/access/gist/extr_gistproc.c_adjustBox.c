#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {TYPE_2__ low; TYPE_1__ high; } ;
typedef  TYPE_3__ BOX ;

/* Variables and functions */
 scalar_t__ float8_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ float8_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
adjustBox(BOX *b, const BOX *addon)
{
	if (float8_lt(b->high.x, addon->high.x))
		b->high.x = addon->high.x;
	if (float8_gt(b->low.x, addon->low.x))
		b->low.x = addon->low.x;
	if (float8_lt(b->high.y, addon->high.y))
		b->high.y = addon->high.y;
	if (float8_gt(b->low.y, addon->low.y))
		b->low.y = addon->low.y;
}