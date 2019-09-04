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
struct sisusb_usb_data {int numobufs; int* urbstatus; } ;

/* Variables and functions */
 int SU_URB_ALLOC ; 
 int SU_URB_BUSY ; 

__attribute__((used)) static int sisusb_outurb_available(struct sisusb_usb_data *sisusb)
{
	int i;

	for (i = 0; i < sisusb->numobufs; i++) {

		if ((sisusb->urbstatus[i] & (SU_URB_BUSY|SU_URB_ALLOC)) == 0)
			return i;

	}

	return -1;
}