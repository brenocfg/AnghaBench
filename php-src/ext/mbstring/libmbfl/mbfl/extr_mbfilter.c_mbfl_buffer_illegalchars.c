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
struct TYPE_7__ {TYPE_2__* filter2; TYPE_1__* filter1; } ;
typedef  TYPE_3__ mbfl_buffer_converter ;
struct TYPE_6__ {scalar_t__ num_illegalchar; } ;
struct TYPE_5__ {scalar_t__ num_illegalchar; } ;

/* Variables and functions */

size_t mbfl_buffer_illegalchars(mbfl_buffer_converter *convd)
{
	size_t num_illegalchars = 0;

	if (convd == NULL) {
		return 0;
	}

	if (convd->filter1 != NULL) {
		num_illegalchars += convd->filter1->num_illegalchar;
	}

	if (convd->filter2 != NULL) {
		num_illegalchars += convd->filter2->num_illegalchar;
	}

	return num_illegalchars;
}