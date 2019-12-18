#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_22__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_21__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_23__ {TYPE_6__ right; TYPE_5__ left; } ;
struct TYPE_18__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_17__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_19__ {TYPE_2__ right; TYPE_1__ left; } ;
struct TYPE_25__ {TYPE_7__ range_box_y; TYPE_3__ range_box_x; } ;
struct TYPE_24__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_20__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_16__ {TYPE_8__ right; TYPE_4__ left; } ;
typedef  TYPE_9__ RectBox ;
typedef  TYPE_10__ RangeBox ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_9__*,TYPE_9__*,int) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static RectBox *
nextRectBox(RectBox *rect_box, RangeBox *centroid, uint8 quadrant)
{
	RectBox    *next_rect_box = (RectBox *) palloc(sizeof(RectBox));

	memcpy(next_rect_box, rect_box, sizeof(RectBox));

	if (quadrant & 0x8)
		next_rect_box->range_box_x.left.low = centroid->left.low;
	else
		next_rect_box->range_box_x.left.high = centroid->left.low;

	if (quadrant & 0x4)
		next_rect_box->range_box_x.right.low = centroid->left.high;
	else
		next_rect_box->range_box_x.right.high = centroid->left.high;

	if (quadrant & 0x2)
		next_rect_box->range_box_y.left.low = centroid->right.low;
	else
		next_rect_box->range_box_y.left.high = centroid->right.low;

	if (quadrant & 0x1)
		next_rect_box->range_box_y.right.low = centroid->right.high;
	else
		next_rect_box->range_box_y.right.high = centroid->right.high;

	return next_rect_box;
}