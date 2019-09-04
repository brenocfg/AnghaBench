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
struct TYPE_2__ {int id; char* name; } ;

/* Variables and functions */
 size_t EOL_LIST_LEN ; 
 TYPE_1__* phpdbg_eol_list ; 

char *phpdbg_eol_name(int id)
{
	size_t i = 0;

	while (i < EOL_LIST_LEN) {

		if (id == phpdbg_eol_list[i].id) {
			return phpdbg_eol_list[i].name;
		}

		i++;
	}

	return NULL;
}