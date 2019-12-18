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
#define  GB_ROM_BANKS_128 137 
#define  GB_ROM_BANKS_16 136 
#define  GB_ROM_BANKS_2 135 
#define  GB_ROM_BANKS_32 134 
#define  GB_ROM_BANKS_4 133 
#define  GB_ROM_BANKS_64 132 
#define  GB_ROM_BANKS_72 131 
#define  GB_ROM_BANKS_8 130 
#define  GB_ROM_BANKS_80 129 
#define  GB_ROM_BANKS_96 128 

int gb_get_rombanks(ut8 id){
	switch (id){
		case GB_ROM_BANKS_2:
			return 2;
		case GB_ROM_BANKS_4:
			return 4;
		case GB_ROM_BANKS_8:
			return 8;
		case GB_ROM_BANKS_16:
			return 16;
		case GB_ROM_BANKS_32:
			return 32;
		case GB_ROM_BANKS_64:
			return 64;
		case GB_ROM_BANKS_128:
			return 128;
		case GB_ROM_BANKS_72:
			return 72;
		case GB_ROM_BANKS_80:
			return 80;
		case GB_ROM_BANKS_96:
			return 96;
		}
	return 2;
}