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
struct fw_region {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct fw_region const*) ; 
 struct fw_region const* regions ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct fw_region * find_region(const char *country) {
	size_t i;

	for (i = 0; i < ARRAY_SIZE(regions); i++) {
		if (strcasecmp(regions[i].name, country) == 0)
			return &regions[i];
	}

	return NULL;
}