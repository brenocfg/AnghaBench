#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned short end; unsigned short start; } ;
struct fl_flow_mask {TYPE_1__ range; } ;

/* Variables and functions */

__attribute__((used)) static unsigned short int fl_mask_range(const struct fl_flow_mask *mask)
{
	return mask->range.end - mask->range.start;
}