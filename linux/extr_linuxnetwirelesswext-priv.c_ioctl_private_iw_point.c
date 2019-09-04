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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_priv_args {int set_args; int get_args; } ;
struct iw_point {int length; int /*<<< orphan*/  pointer; } ;
typedef  int (* iw_handler ) (struct net_device*,struct iw_request_info*,union iwreq_data*,char*) ;

/* Variables and functions */
 int E2BIG ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IW_IS_GET (unsigned int) ; 
 scalar_t__ IW_IS_SET (unsigned int) ; 
 int IW_PRIV_SIZE_FIXED ; 
 int IW_PRIV_SIZE_MASK ; 
 int adjust_priv_size (int,struct iw_point*) ; 
 scalar_t__ copy_from_user (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_private_iw_point(struct iw_point *iwp, unsigned int cmd,
				  const struct iw_priv_args *descr,
				  iw_handler handler, struct net_device *dev,
				  struct iw_request_info *info, int extra_size)
{
	char *extra;
	int err;

	/* Check what user space is giving us */
	if (IW_IS_SET(cmd)) {
		if (!iwp->pointer && iwp->length != 0)
			return -EFAULT;

		if (iwp->length > (descr->set_args & IW_PRIV_SIZE_MASK))
			return -E2BIG;
	} else if (!iwp->pointer)
		return -EFAULT;

	extra = kzalloc(extra_size, GFP_KERNEL);
	if (!extra)
		return -ENOMEM;

	/* If it is a SET, get all the extra data in here */
	if (IW_IS_SET(cmd) && (iwp->length != 0)) {
		if (copy_from_user(extra, iwp->pointer, extra_size)) {
			err = -EFAULT;
			goto out;
		}
	}

	/* Call the handler */
	err = handler(dev, info, (union iwreq_data *) iwp, extra);

	/* If we have something to return to the user */
	if (!err && IW_IS_GET(cmd)) {
		/* Adjust for the actual length if it's variable,
		 * avoid leaking kernel bits outside.
		 */
		if (!(descr->get_args & IW_PRIV_SIZE_FIXED))
			extra_size = adjust_priv_size(descr->get_args, iwp);

		if (copy_to_user(iwp->pointer, extra, extra_size))
			err =  -EFAULT;
	}

out:
	kfree(extra);
	return err;
}