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
struct TYPE_10__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;
struct TYPE_8__ {int /*<<< orphan*/  low; } ;
struct TYPE_7__ {int /*<<< orphan*/  high; } ;
struct TYPE_9__ {TYPE_2__ left; TYPE_1__ right; } ;
typedef  TYPE_3__ RangeBox ;
typedef  TYPE_4__ Range ;

/* Variables and functions */
 scalar_t__ FPge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FPle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
contain2D(RangeBox *range_box, Range *query)
{
	return FPge(range_box->right.high, query->high) &&
		FPle(range_box->left.low, query->low);
}