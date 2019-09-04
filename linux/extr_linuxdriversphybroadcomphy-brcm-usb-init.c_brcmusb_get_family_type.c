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
typedef  int u32 ;
struct brcm_usb_init_params {int family_id; } ;
typedef  enum brcm_family_type { ____Placeholder_brcm_family_type } brcm_family_type ;
struct TYPE_2__ {int id; int type; } ;

/* Variables and functions */
 TYPE_1__* id_to_type_table ; 

__attribute__((used)) static enum brcm_family_type brcmusb_get_family_type(
	struct brcm_usb_init_params *params)
{
	int last_type = -1;
	u32 last_family = 0;
	u32 family_no_major;
	unsigned int x;
	u32 family;

	family = params->family_id & 0xfffffff0;
	family_no_major = params->family_id & 0xffffff00;
	for (x = 0; id_to_type_table[x].id; x++) {
		if (family == id_to_type_table[x].id)
			return id_to_type_table[x].type;
		if (family_no_major == (id_to_type_table[x].id & 0xffffff00))
			if (family > id_to_type_table[x].id &&
			    last_family < id_to_type_table[x].id) {
				last_family = id_to_type_table[x].id;
				last_type = id_to_type_table[x].type;
			}
	}

	/* If no match, return the default family */
	if (last_type == -1)
		return id_to_type_table[x].type;
	return last_type;
}