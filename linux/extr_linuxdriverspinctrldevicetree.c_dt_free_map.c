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
struct pinctrl_ops {int /*<<< orphan*/  (* dt_free_map ) (struct pinctrl_dev*,struct pinctrl_map*,unsigned int) ;} ;
struct pinctrl_map {int dummy; } ;
struct pinctrl_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {struct pinctrl_ops* pctlops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pinctrl_map*) ; 
 int /*<<< orphan*/  stub1 (struct pinctrl_dev*,struct pinctrl_map*,unsigned int) ; 

__attribute__((used)) static void dt_free_map(struct pinctrl_dev *pctldev,
		     struct pinctrl_map *map, unsigned num_maps)
{
	if (pctldev) {
		const struct pinctrl_ops *ops = pctldev->desc->pctlops;
		if (ops->dt_free_map)
			ops->dt_free_map(pctldev, map, num_maps);
	} else {
		/* There is no pctldev for PIN_MAP_TYPE_DUMMY_STATE */
		kfree(map);
	}
}