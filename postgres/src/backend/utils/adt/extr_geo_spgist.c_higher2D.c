#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  high; } ;
struct TYPE_8__ {int /*<<< orphan*/  high; } ;
struct TYPE_7__ {int /*<<< orphan*/  high; } ;
struct TYPE_9__ {TYPE_2__ right; TYPE_1__ left; } ;
typedef  TYPE_3__ RangeBox ;
typedef  TYPE_4__ Range ;

/* Variables and functions */
 scalar_t__ FPgt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
higher2D(RangeBox *range_box, Range *query)
{
	return FPgt(range_box->left.high, query->high) &&
		FPgt(range_box->right.high, query->high);
}