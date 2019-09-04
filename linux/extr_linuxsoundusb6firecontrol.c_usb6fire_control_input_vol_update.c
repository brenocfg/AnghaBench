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
struct control_runtime {int ivol_updated; int* input_vol; TYPE_1__* chip; } ;
struct comm_runtime {int /*<<< orphan*/  (* write8 ) (struct comm_runtime*,int,int,int) ;} ;
struct TYPE_2__ {struct comm_runtime* comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct comm_runtime*,int,int,int) ; 

__attribute__((used)) static void usb6fire_control_input_vol_update(struct control_runtime *rt)
{
	struct comm_runtime *comm_rt = rt->chip->comm;
	int i;

	if (comm_rt)
		for (i = 0; i < 2; i++)
			if (!(rt->ivol_updated & (1 << i))) {
				comm_rt->write8(comm_rt, 0x12, 0x1c + i,
					rt->input_vol[i] & 0x3f);
				rt->ivol_updated |= 1 << i;
			}
}