#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct u132 {int hc_control; int hc_roothub_status; int hc_roothub_a; int num_ports; int* hc_roothub_portstatus; TYPE_1__* platform_dev; } ;
struct TYPE_4__ {int status; int a; int* portstatus; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int control ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 TYPE_2__ roothub ; 
 int u132_read_pcimem (struct u132*,int,int*) ; 

__attribute__((used)) static int read_roothub_info(struct u132 *u132)
{
	u32 revision;
	int retval;
	retval = u132_read_pcimem(u132, revision, &revision);
	if (retval) {
		dev_err(&u132->platform_dev->dev, "error %d accessing device co"
			"ntrol\n", retval);
		return retval;
	} else if ((revision & 0xFF) == 0x10) {
	} else if ((revision & 0xFF) == 0x11) {
	} else {
		dev_err(&u132->platform_dev->dev, "device revision is not valid"
			" %08X\n", revision);
		return -ENODEV;
	}
	retval = u132_read_pcimem(u132, control, &u132->hc_control);
	if (retval) {
		dev_err(&u132->platform_dev->dev, "error %d accessing device co"
			"ntrol\n", retval);
		return retval;
	}
	retval = u132_read_pcimem(u132, roothub.status,
		&u132->hc_roothub_status);
	if (retval) {
		dev_err(&u132->platform_dev->dev, "error %d accessing device re"
			"g roothub.status\n", retval);
		return retval;
	}
	retval = u132_read_pcimem(u132, roothub.a, &u132->hc_roothub_a);
	if (retval) {
		dev_err(&u132->platform_dev->dev, "error %d accessing device re"
			"g roothub.a\n", retval);
		return retval;
	}
	{
		int I = u132->num_ports;
		int i = 0;
		while (I-- > 0) {
			retval = u132_read_pcimem(u132, roothub.portstatus[i],
				&u132->hc_roothub_portstatus[i]);
			if (retval) {
				dev_err(&u132->platform_dev->dev, "error %d acc"
					"essing device roothub.portstatus[%d]\n"
					, retval, i);
				return retval;
			} else
				i += 1;
		}
	}
	return 0;
}