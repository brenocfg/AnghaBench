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
typedef  enum chip_type { ____Placeholder_chip_type } chip_type ;
struct TYPE_2__ {char const* name; int chip_id; } ;

/* Variables and functions */
 TYPE_1__* chip_info_table ; 

__attribute__((used)) static const char *get_chip_name(enum chip_type chip_id)
{
	int i;
	for (i = 0; chip_info_table[i].name != NULL; i++)
		if (chip_info_table[i].chip_id == chip_id)
			break;
	return chip_info_table[i].name;
}