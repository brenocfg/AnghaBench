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
struct fw_map {scalar_t__ name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct fw_map*) ; 
 struct fw_map* fw_mapping ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

struct fw_map *wil_find_fw_mapping(const char *section)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(fw_mapping); i++)
		if (fw_mapping[i].name &&
		    !strcmp(section, fw_mapping[i].name))
			return &fw_mapping[i];

	return NULL;
}