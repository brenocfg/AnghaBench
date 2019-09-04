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
struct aspeed_pin_config_map {int arg; int val; int param; } ;
typedef  int s64 ;
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;
typedef  enum aspeed_pin_config_map_type { ____Placeholder_aspeed_pin_config_map_type } aspeed_pin_config_map_type ;

/* Variables and functions */
 int ARRAY_SIZE (struct aspeed_pin_config_map*) ; 
#define  MAP_TYPE_ARG 129 
#define  MAP_TYPE_VAL 128 
 struct aspeed_pin_config_map* pin_config_map ; 

__attribute__((used)) static const struct aspeed_pin_config_map *find_pinconf_map(
		enum pin_config_param param,
		enum aspeed_pin_config_map_type type,
		s64 value)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(pin_config_map); i++) {
		const struct aspeed_pin_config_map *elem;
		bool match;

		elem = &pin_config_map[i];

		switch (type) {
		case MAP_TYPE_ARG:
			match = (elem->arg == -1 || elem->arg == value);
			break;
		case MAP_TYPE_VAL:
			match = (elem->val == value);
			break;
		}

		if (param == elem->param && match)
			return elem;
	}

	return NULL;
}