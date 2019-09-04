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
typedef  enum iscsi_ipaddress_state { ____Placeholder_iscsi_ipaddress_state } iscsi_ipaddress_state ;
struct TYPE_3__ {int value; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* iscsi_ipaddress_state_names ; 

char *iscsi_get_ipaddress_state_name(enum iscsi_ipaddress_state port_state)
{
	int i;
	char *state = NULL;

	for (i = 0; i < ARRAY_SIZE(iscsi_ipaddress_state_names); i++) {
		if (iscsi_ipaddress_state_names[i].value == port_state) {
			state = iscsi_ipaddress_state_names[i].name;
			break;
		}
	}
	return state;
}