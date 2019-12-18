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
struct map {char const* perf; scalar_t__ json; } ;
typedef  int /*<<< orphan*/  jsmntok_t ;

/* Variables and functions */
 scalar_t__ json_streq (char*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static const char *field_to_perf(struct map *table, char *map, jsmntok_t *val)
{
	int i;

	for (i = 0; table[i].json; i++) {
		if (json_streq(map, val, table[i].json))
			return table[i].perf;
	}
	return NULL;
}