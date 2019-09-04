#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ax25_fwd_struct {int /*<<< orphan*/  port_to; int /*<<< orphan*/  port_from; } ;
struct TYPE_3__ {int /*<<< orphan*/ * forward; int /*<<< orphan*/ * dev; } ;
typedef  TYPE_1__ ax25_dev ;

/* Variables and functions */
 int EINVAL ; 
#define  SIOCAX25ADDFWD 129 
#define  SIOCAX25DELFWD 128 
 TYPE_1__* ax25_addr_ax25dev (int /*<<< orphan*/ *) ; 

int ax25_fwd_ioctl(unsigned int cmd, struct ax25_fwd_struct *fwd)
{
	ax25_dev *ax25_dev, *fwd_dev;

	if ((ax25_dev = ax25_addr_ax25dev(&fwd->port_from)) == NULL)
		return -EINVAL;

	switch (cmd) {
	case SIOCAX25ADDFWD:
		if ((fwd_dev = ax25_addr_ax25dev(&fwd->port_to)) == NULL)
			return -EINVAL;
		if (ax25_dev->forward != NULL)
			return -EINVAL;
		ax25_dev->forward = fwd_dev->dev;
		break;

	case SIOCAX25DELFWD:
		if (ax25_dev->forward == NULL)
			return -EINVAL;
		ax25_dev->forward = NULL;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}