#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ upper; scalar_t__ lower; } ;
typedef  TYPE_1__ SEG ;

/* Variables and functions */
 scalar_t__ Abs (scalar_t__) ; 

__attribute__((used)) static void
rt_seg_size(SEG *a, float *size)
{
	if (a == (SEG *) NULL || a->upper <= a->lower)
		*size = 0.0;
	else
		*size = (float) Abs(a->upper - a->lower);

	return;
}