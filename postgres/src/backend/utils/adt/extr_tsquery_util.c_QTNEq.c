#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_6__ {int sign; } ;
typedef  TYPE_1__ QTNode ;

/* Variables and functions */
 scalar_t__ QTNodeCompare (TYPE_1__*,TYPE_1__*) ; 

bool
QTNEq(QTNode *a, QTNode *b)
{
	uint32		sign = a->sign & b->sign;

	if (!(sign == a->sign && sign == b->sign))
		return false;

	return (QTNodeCompare(a, b) == 0) ? true : false;
}