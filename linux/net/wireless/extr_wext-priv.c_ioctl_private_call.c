#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct iwreq {TYPE_1__ u; } ;
struct iw_request_info {int dummy; } ;
struct iw_priv_args {int dummy; } ;
typedef  int (* iw_handler ) (struct net_device*,struct iw_request_info*,TYPE_1__*,char*) ;

/* Variables and functions */
 int EINVAL ; 
 int EIWCOMMIT ; 
 int call_commit_handler (struct net_device*) ; 
 int get_priv_descr_and_size (struct net_device*,unsigned int,struct iw_priv_args const**) ; 
 int ioctl_private_iw_point (int /*<<< orphan*/ *,unsigned int,struct iw_priv_args const*,int (*) (struct net_device*,struct iw_request_info*,TYPE_1__*,char*),struct net_device*,struct iw_request_info*,int) ; 

int ioctl_private_call(struct net_device *dev, struct iwreq *iwr,
		       unsigned int cmd, struct iw_request_info *info,
		       iw_handler handler)
{
	int extra_size = 0, ret = -EINVAL;
	const struct iw_priv_args *descr;

	extra_size = get_priv_descr_and_size(dev, cmd, &descr);

	/* Check if we have a pointer to user space data or not. */
	if (extra_size == 0) {
		/* No extra arguments. Trivial to handle */
		ret = handler(dev, info, &(iwr->u), (char *) &(iwr->u));
	} else {
		ret = ioctl_private_iw_point(&iwr->u.data, cmd, descr,
					     handler, dev, info, extra_size);
	}

	/* Call commit handler if needed and defined */
	if (ret == -EIWCOMMIT)
		ret = call_commit_handler(dev);

	return ret;
}