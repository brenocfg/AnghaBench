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
struct rtl8366_smi {int num_ports; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* enable_port ) (struct rtl8366_smi*,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct rtl8366_smi*,int,int) ; 

int rtl8366_enable_all_ports(struct rtl8366_smi *smi, int enable)
{
	int port;
	int err;

	for (port = 0; port < smi->num_ports; port++) {
		err = smi->ops->enable_port(smi, port, enable);
		if (err)
			return err;
	}

	return 0;
}