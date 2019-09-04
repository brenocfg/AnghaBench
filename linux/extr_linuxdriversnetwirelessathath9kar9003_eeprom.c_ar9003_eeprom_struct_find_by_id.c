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
struct ar9300_eeprom {int templateVersion; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ar9300_eeprom const**) ; 
 struct ar9300_eeprom const** ar9300_eep_templates ; 

__attribute__((used)) static const struct ar9300_eeprom *ar9003_eeprom_struct_find_by_id(int id)
{
	int it;

	for (it = 0; it < ARRAY_SIZE(ar9300_eep_templates); it++)
		if (ar9300_eep_templates[it]->templateVersion == id)
			return ar9300_eep_templates[it];
	return NULL;
}