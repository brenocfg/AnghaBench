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
struct battery_property_map {int value; scalar_t__ key; } ;

/* Variables and functions */
 int MAX_KEYLENGTH ; 
 scalar_t__ strncasecmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int strnlen (char*,int) ; 

__attribute__((used)) static int map_get_value(struct battery_property_map *map, const char *key,
				int def_val)
{
	char buf[MAX_KEYLENGTH];
	int cr;

	strncpy(buf, key, MAX_KEYLENGTH);
	buf[MAX_KEYLENGTH-1] = '\0';

	cr = strnlen(buf, MAX_KEYLENGTH) - 1;
	if (cr < 0)
		return def_val;
	if (buf[cr] == '\n')
		buf[cr] = '\0';

	while (map->key) {
		if (strncasecmp(map->key, buf, MAX_KEYLENGTH) == 0)
			return map->value;
		map++;
	}

	return def_val;
}