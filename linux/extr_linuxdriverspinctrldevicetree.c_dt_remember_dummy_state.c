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
struct pinctrl_map {int /*<<< orphan*/  type; } ;
struct pinctrl {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_DUMMY_STATE ; 
 int dt_remember_or_free_map (struct pinctrl*,char const*,int /*<<< orphan*/ *,struct pinctrl_map*,int) ; 
 struct pinctrl_map* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dt_remember_dummy_state(struct pinctrl *p, const char *statename)
{
	struct pinctrl_map *map;

	map = kzalloc(sizeof(*map), GFP_KERNEL);
	if (!map)
		return -ENOMEM;

	/* There is no pctldev for PIN_MAP_TYPE_DUMMY_STATE */
	map->type = PIN_MAP_TYPE_DUMMY_STATE;

	return dt_remember_or_free_map(p, statename, NULL, map, 1);
}