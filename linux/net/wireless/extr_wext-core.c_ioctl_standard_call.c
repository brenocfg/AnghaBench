#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct iwreq {TYPE_1__ u; } ;
struct iw_request_info {int dummy; } ;
struct iw_ioctl_description {scalar_t__ header_type; int flags; } ;
typedef  int (* iw_handler ) (struct net_device*,struct iw_request_info*,TYPE_1__*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int EINVAL ; 
 int EIWCOMMIT ; 
 int EOPNOTSUPP ; 
 int IW_DESCR_FLAG_EVENT ; 
 scalar_t__ IW_HEADER_TYPE_POINT ; 
 size_t IW_IOCTL_IDX (unsigned int) ; 
 int call_commit_handler (struct net_device*) ; 
 int ioctl_standard_iw_point (int /*<<< orphan*/ *,unsigned int,struct iw_ioctl_description const*,int (*) (struct net_device*,struct iw_request_info*,TYPE_1__*,int /*<<< orphan*/ *),struct net_device*,struct iw_request_info*) ; 
 struct iw_ioctl_description* standard_ioctl ; 
 size_t standard_ioctl_num ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,unsigned int,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioctl_standard_call(struct net_device *	dev,
			       struct iwreq		*iwr,
			       unsigned int		cmd,
			       struct iw_request_info	*info,
			       iw_handler		handler)
{
	const struct iw_ioctl_description *	descr;
	int					ret = -EINVAL;

	/* Get the description of the IOCTL */
	if (IW_IOCTL_IDX(cmd) >= standard_ioctl_num)
		return -EOPNOTSUPP;
	descr = &(standard_ioctl[IW_IOCTL_IDX(cmd)]);

	/* Check if we have a pointer to user space data or not */
	if (descr->header_type != IW_HEADER_TYPE_POINT) {

		/* No extra arguments. Trivial to handle */
		ret = handler(dev, info, &(iwr->u), NULL);

		/* Generate an event to notify listeners of the change */
		if ((descr->flags & IW_DESCR_FLAG_EVENT) &&
		   ((ret == 0) || (ret == -EIWCOMMIT)))
			wireless_send_event(dev, cmd, &(iwr->u), NULL);
	} else {
		ret = ioctl_standard_iw_point(&iwr->u.data, cmd, descr,
					      handler, dev, info);
	}

	/* Call commit handler if needed and defined */
	if (ret == -EIWCOMMIT)
		ret = call_commit_handler(dev);

	/* Here, we will generate the appropriate event if needed */

	return ret;
}