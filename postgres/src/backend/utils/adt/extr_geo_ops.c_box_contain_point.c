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
struct TYPE_8__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_7__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_10__ {TYPE_2__ low; TYPE_1__ high; } ;
struct TYPE_9__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_3__ Point ;
typedef  TYPE_4__ BOX ;

/* Variables and functions */

__attribute__((used)) static bool
box_contain_point(BOX *box, Point *point)
{
	return box->high.x >= point->x && box->low.x <= point->x &&
		box->high.y >= point->y && box->low.y <= point->y;
}