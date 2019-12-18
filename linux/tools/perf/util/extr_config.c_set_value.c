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
struct perf_config_item {char* value; } ;

/* Variables and functions */
 char* strdup (char const*) ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static int set_value(struct perf_config_item *item, const char *value)
{
	char *val = strdup(value);

	if (!val)
		return -1;

	zfree(&item->value);
	item->value = val;
	return 0;
}