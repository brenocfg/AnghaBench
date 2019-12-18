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
struct control_runtime {TYPE_1__* chip; } ;
struct comm_runtime {int (* write16 ) (struct comm_runtime*,int,int,int,int) ;} ;
struct TYPE_2__ {struct comm_runtime* comm; } ;

/* Variables and functions */
 int stub1 (struct comm_runtime*,int,int,int,int) ; 
 int stub2 (struct comm_runtime*,int,int,int,int) ; 

__attribute__((used)) static int usb6fire_control_set_channels(
	struct control_runtime *rt, int n_analog_out,
	int n_analog_in, bool spdif_out, bool spdif_in)
{
	int ret;
	struct comm_runtime *comm_rt = rt->chip->comm;

	/* enable analog inputs and outputs
	 * (one bit per stereo-channel) */
	ret = comm_rt->write16(comm_rt, 0x02, 0x02,
			(1 << (n_analog_out / 2)) - 1,
			(1 << (n_analog_in / 2)) - 1);
	if (ret < 0)
		return ret;

	/* disable digital inputs and outputs */
	/* TODO: use spdif_x to enable/disable digital channels */
	ret = comm_rt->write16(comm_rt, 0x02, 0x03, 0x00, 0x00);
	if (ret < 0)
		return ret;

	return 0;
}