#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_14__ {TYPE_4__ high; TYPE_2__ low; } ;
struct TYPE_9__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_11__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_13__ {TYPE_1__ right; TYPE_3__ left; } ;
typedef  TYPE_5__ RangeBox ;
typedef  TYPE_6__ BOX ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

__attribute__((used)) static RangeBox *
getRangeBox(BOX *box)
{
	RangeBox   *range_box = (RangeBox *) palloc(sizeof(RangeBox));

	range_box->left.low = box->low.x;
	range_box->left.high = box->high.x;

	range_box->right.low = box->low.y;
	range_box->right.high = box->high.y;

	return range_box;
}