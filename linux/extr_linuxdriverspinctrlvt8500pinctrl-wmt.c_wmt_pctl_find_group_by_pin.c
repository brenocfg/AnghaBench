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
typedef  scalar_t__ u32 ;
struct wmt_pinctrl_data {int npins; TYPE_1__* pins; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int wmt_pctl_find_group_by_pin(struct wmt_pinctrl_data *data, u32 pin)
{
	int i;

	for (i = 0; i < data->npins; i++) {
		if (data->pins[i].number == pin)
			return i;
	}

	return -EINVAL;
}