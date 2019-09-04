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
struct TYPE_3__ {scalar_t__ length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct net_device {TYPE_2__* wireless_handlers; } ;
struct iw_request_info {int dummy; } ;
struct iw_priv_args {int dummy; } ;
struct TYPE_4__ {scalar_t__ num_private_args; int /*<<< orphan*/ * private_args; } ;

/* Variables and functions */
 int E2BIG ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

int iw_handler_get_private(struct net_device *		dev,
			   struct iw_request_info *	info,
			   union iwreq_data *		wrqu,
			   char *			extra)
{
	/* Check if the driver has something to export */
	if ((dev->wireless_handlers->num_private_args == 0) ||
	   (dev->wireless_handlers->private_args == NULL))
		return -EOPNOTSUPP;

	/* Check if there is enough buffer up there */
	if (wrqu->data.length < dev->wireless_handlers->num_private_args) {
		/* User space can't know in advance how large the buffer
		 * needs to be. Give it a hint, so that we can support
		 * any size buffer we want somewhat efficiently... */
		wrqu->data.length = dev->wireless_handlers->num_private_args;
		return -E2BIG;
	}

	/* Set the number of available ioctls. */
	wrqu->data.length = dev->wireless_handlers->num_private_args;

	/* Copy structure to the user buffer. */
	memcpy(extra, dev->wireless_handlers->private_args,
	       sizeof(struct iw_priv_args) * wrqu->data.length);

	return 0;
}