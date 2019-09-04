#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pinctrl_map {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void rockchip_dt_free_map(struct pinctrl_dev *pctldev,
				    struct pinctrl_map *map, unsigned num_maps)
{
}