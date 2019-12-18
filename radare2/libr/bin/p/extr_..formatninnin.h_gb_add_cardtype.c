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
typedef  int ut8 ;

/* Variables and functions */
 int GB_CAM ; 
#define  GB_HUC1 130 
#define  GB_HUC3 129 
#define  GB_TAMA5 128 
 char** gb_card_type_str ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

void gb_add_cardtype(char *type, ut8 cardcode){
	strcat (type,"\ncard\t");
	switch (cardcode){
		case GB_TAMA5:
		case GB_HUC3:
		case GB_HUC1:
			strcat (type,gb_card_type_str[cardcode-240]);
			break;
		case 0x15:
		case 0x16:
		case 0x17:
			strcat (type,"XXX");
			break;
		default:
			if (cardcode>GB_CAM) {
				strcat (type,"XXX");
				return;
			}
			strcat (type,gb_card_type_str[cardcode]);
			break;
	}
}