#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum raid_state { ____Placeholder_raid_state } raid_state ;
struct TYPE_3__ {int value; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* raid_states ; 

__attribute__((used)) static const char *raid_state_name(enum raid_state state)
{
	int i;
	char *name = NULL;

	for (i = 0; i < ARRAY_SIZE(raid_states); i++) {
		if (raid_states[i].value == state) {
			name = raid_states[i].name;
			break;
		}
	}
	return name;
}