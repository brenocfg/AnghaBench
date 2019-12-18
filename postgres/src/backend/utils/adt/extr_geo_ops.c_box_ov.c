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
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {TYPE_1__ high; TYPE_2__ low; } ;
typedef  TYPE_3__ BOX ;

/* Variables and functions */
 scalar_t__ FPle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
box_ov(BOX *box1, BOX *box2)
{
	return (FPle(box1->low.x, box2->high.x) &&
			FPle(box2->low.x, box1->high.x) &&
			FPle(box1->low.y, box2->high.y) &&
			FPle(box2->low.y, box1->high.y));
}