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
typedef  int u16 ;
struct u132 {int dummy; } ;
struct TYPE_2__ {int* portstatus; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PORT_RESET_HW_MSEC ; 
 int PORT_RESET_MSEC ; 
 int RH_PS_CCS ; 
 int RH_PS_PRS ; 
 int RH_PS_PRSC ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 TYPE_1__ roothub ; 
 scalar_t__ tick_before (int,int) ; 
 int u132_read_pcimem (struct u132*,int,int*) ; 
 int u132_write_pcimem (struct u132*,int,int) ; 

__attribute__((used)) static int u132_roothub_portreset(struct u132 *u132, int port_index)
{
	int retval;
	u32 fmnumber;
	u16 now;
	u16 reset_done;
	retval = u132_read_pcimem(u132, fmnumber, &fmnumber);
	if (retval)
		return retval;
	now = fmnumber;
	reset_done = now + PORT_RESET_MSEC;
	do {
		u32 portstat;
		do {
			retval = u132_read_pcimem(u132,
				roothub.portstatus[port_index], &portstat);
			if (retval)
				return retval;
			if (RH_PS_PRS & portstat)
				continue;
			else
				break;
		} while (tick_before(now, reset_done));
		if (RH_PS_PRS & portstat)
			return -ENODEV;
		if (RH_PS_CCS & portstat) {
			if (RH_PS_PRSC & portstat) {
				retval = u132_write_pcimem(u132,
					roothub.portstatus[port_index],
					RH_PS_PRSC);
				if (retval)
					return retval;
			}
		} else
			break;	/* start the next reset,
				sleep till it's probably done */
		retval = u132_write_pcimem(u132, roothub.portstatus[port_index],
			 RH_PS_PRS);
		if (retval)
			return retval;
		msleep(PORT_RESET_HW_MSEC);
		retval = u132_read_pcimem(u132, fmnumber, &fmnumber);
		if (retval)
			return retval;
		now = fmnumber;
	} while (tick_before(now, reset_done));
	return 0;
}