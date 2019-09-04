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
struct brcm_usb_init_params {int selected_family; int /*<<< orphan*/  family_name; int /*<<< orphan*/ * usb_reg_bits_map; } ;

/* Variables and functions */
 int brcmusb_get_family_type (struct brcm_usb_init_params*) ; 
 int /*<<< orphan*/ * family_names ; 
 int /*<<< orphan*/ ** usb_reg_bits_map_table ; 

void brcm_usb_set_family_map(struct brcm_usb_init_params *params)
{
	int fam;

	fam = brcmusb_get_family_type(params);
	params->selected_family = fam;
	params->usb_reg_bits_map =
		&usb_reg_bits_map_table[fam][0];
	params->family_name = family_names[fam];
}