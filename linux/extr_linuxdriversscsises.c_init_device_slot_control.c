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
struct enclosure_component {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ENCLOSURE_COMPONENT_DEVICE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static void init_device_slot_control(unsigned char *dest_desc,
				     struct enclosure_component *ecomp,
				     unsigned char *status)
{
	memcpy(dest_desc, status, 4);
	dest_desc[0] = 0;
	/* only clear byte 1 for ENCLOSURE_COMPONENT_DEVICE */
	if (ecomp->type == ENCLOSURE_COMPONENT_DEVICE)
		dest_desc[1] = 0;
	dest_desc[2] &= 0xde;
	dest_desc[3] &= 0x3c;
}