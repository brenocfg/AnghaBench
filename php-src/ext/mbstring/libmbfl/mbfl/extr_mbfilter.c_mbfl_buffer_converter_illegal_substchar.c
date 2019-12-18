#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* filter1; TYPE_1__* filter2; } ;
typedef  TYPE_3__ mbfl_buffer_converter ;
struct TYPE_6__ {int illegal_substchar; } ;
struct TYPE_5__ {int illegal_substchar; } ;

/* Variables and functions */

int
mbfl_buffer_converter_illegal_substchar(mbfl_buffer_converter *convd, int substchar)
{
	if (convd != NULL) {
		if (convd->filter2 != NULL) {
			convd->filter2->illegal_substchar = substchar;
		} else if (convd->filter1 != NULL) {
			convd->filter1->illegal_substchar = substchar;
		} else {
			return 0;
		}
	}

	return 1;
}