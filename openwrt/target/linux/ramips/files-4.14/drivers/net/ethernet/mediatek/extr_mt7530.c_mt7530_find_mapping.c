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
struct mt7530_mapping {int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mt7530_mapping*) ; 
 struct mt7530_mapping* mt7530_defaults ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

struct mt7530_mapping*
mt7530_find_mapping(struct device_node *np)
{
	const char *map;
	int i;

	if (of_property_read_string(np, "mediatek,portmap", &map))
		return NULL;

	for (i = 0; i < ARRAY_SIZE(mt7530_defaults); i++)
		if (!strcmp(map, mt7530_defaults[i].name))
			return &mt7530_defaults[i];

	return NULL;
}