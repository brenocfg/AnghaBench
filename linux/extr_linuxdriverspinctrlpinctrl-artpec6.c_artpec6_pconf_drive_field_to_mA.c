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

/* Variables and functions */
 unsigned int ARTPEC6_DRIVE_4mA ; 
#define  ARTPEC6_DRIVE_4mA_SET 131 
 unsigned int ARTPEC6_DRIVE_6mA ; 
#define  ARTPEC6_DRIVE_6mA_SET 130 
 unsigned int ARTPEC6_DRIVE_8mA ; 
#define  ARTPEC6_DRIVE_8mA_SET 129 
 unsigned int ARTPEC6_DRIVE_9mA ; 
#define  ARTPEC6_DRIVE_9mA_SET 128 

__attribute__((used)) static unsigned int artpec6_pconf_drive_field_to_mA(int field)
{
	switch (field) {
	case ARTPEC6_DRIVE_4mA_SET:
		return ARTPEC6_DRIVE_4mA;
	case ARTPEC6_DRIVE_6mA_SET:
		return ARTPEC6_DRIVE_6mA;
	case ARTPEC6_DRIVE_8mA_SET:
		return ARTPEC6_DRIVE_8mA;
	case ARTPEC6_DRIVE_9mA_SET:
		return ARTPEC6_DRIVE_9mA;
	default:
		/* Shouldn't happen */
		return 0;
	}
}