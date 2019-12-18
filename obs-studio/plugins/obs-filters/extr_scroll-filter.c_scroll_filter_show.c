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
struct TYPE_2__ {float x; float y; } ;
struct scroll_filter_data {TYPE_1__ offset; } ;

/* Variables and functions */

__attribute__((used)) static void scroll_filter_show(void *data)
{
	struct scroll_filter_data *filter = data;
	filter->offset.x = 0.0f;
	filter->offset.y = 0.0f;
}