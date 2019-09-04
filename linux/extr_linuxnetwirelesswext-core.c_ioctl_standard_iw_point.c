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
struct iw_point {int length; int /*<<< orphan*/  pointer; } ;
struct iw_ioctl_description {int max_tokens; int token_size; int min_tokens; int flags; } ;
struct iw_encode_ext {scalar_t__ key_len; } ;
typedef  int (* iw_handler ) (struct net_device*,struct iw_request_info*,union iwreq_data*,char*) ;

/* Variables and functions */
 int E2BIG ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIWCOMMIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IW_DESCR_FLAG_EVENT ; 
 int IW_DESCR_FLAG_NOMAX ; 
 int IW_DESCR_FLAG_RESTRICT ; 
 unsigned int IW_ESSID_MAX_SIZE ; 
 scalar_t__ IW_IS_GET (unsigned int) ; 
 scalar_t__ IW_IS_SET (unsigned int) ; 
#define  SIOCGIWESSID 131 
#define  SIOCGIWNICKN 130 
 unsigned int SIOCSIWENCODEEXT ; 
#define  SIOCSIWESSID 129 
#define  SIOCSIWNICKN 128 
 int copy_from_user (char*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,unsigned int,union iwreq_data*,char*) ; 

__attribute__((used)) static int ioctl_standard_iw_point(struct iw_point *iwp, unsigned int cmd,
				   const struct iw_ioctl_description *descr,
				   iw_handler handler, struct net_device *dev,
				   struct iw_request_info *info)
{
	int err, extra_size, user_length = 0, essid_compat = 0;
	char *extra;

	/* Calculate space needed by arguments. Always allocate
	 * for max space.
	 */
	extra_size = descr->max_tokens * descr->token_size;

	/* Check need for ESSID compatibility for WE < 21 */
	switch (cmd) {
	case SIOCSIWESSID:
	case SIOCGIWESSID:
	case SIOCSIWNICKN:
	case SIOCGIWNICKN:
		if (iwp->length == descr->max_tokens + 1)
			essid_compat = 1;
		else if (IW_IS_SET(cmd) && (iwp->length != 0)) {
			char essid[IW_ESSID_MAX_SIZE + 1];
			unsigned int len;
			len = iwp->length * descr->token_size;

			if (len > IW_ESSID_MAX_SIZE)
				return -EFAULT;

			err = copy_from_user(essid, iwp->pointer, len);
			if (err)
				return -EFAULT;

			if (essid[iwp->length - 1] == '\0')
				essid_compat = 1;
		}
		break;
	default:
		break;
	}

	iwp->length -= essid_compat;

	/* Check what user space is giving us */
	if (IW_IS_SET(cmd)) {
		/* Check NULL pointer */
		if (!iwp->pointer && iwp->length != 0)
			return -EFAULT;
		/* Check if number of token fits within bounds */
		if (iwp->length > descr->max_tokens)
			return -E2BIG;
		if (iwp->length < descr->min_tokens)
			return -EINVAL;
	} else {
		/* Check NULL pointer */
		if (!iwp->pointer)
			return -EFAULT;
		/* Save user space buffer size for checking */
		user_length = iwp->length;

		/* Don't check if user_length > max to allow forward
		 * compatibility. The test user_length < min is
		 * implied by the test at the end.
		 */

		/* Support for very large requests */
		if ((descr->flags & IW_DESCR_FLAG_NOMAX) &&
		    (user_length > descr->max_tokens)) {
			/* Allow userspace to GET more than max so
			 * we can support any size GET requests.
			 * There is still a limit : -ENOMEM.
			 */
			extra_size = user_length * descr->token_size;

			/* Note : user_length is originally a __u16,
			 * and token_size is controlled by us,
			 * so extra_size won't get negative and
			 * won't overflow...
			 */
		}
	}

	/* kzalloc() ensures NULL-termination for essid_compat. */
	extra = kzalloc(extra_size, GFP_KERNEL);
	if (!extra)
		return -ENOMEM;

	/* If it is a SET, get all the extra data in here */
	if (IW_IS_SET(cmd) && (iwp->length != 0)) {
		if (copy_from_user(extra, iwp->pointer,
				   iwp->length *
				   descr->token_size)) {
			err = -EFAULT;
			goto out;
		}

		if (cmd == SIOCSIWENCODEEXT) {
			struct iw_encode_ext *ee = (void *) extra;

			if (iwp->length < sizeof(*ee) + ee->key_len) {
				err = -EFAULT;
				goto out;
			}
		}
	}

	if (IW_IS_GET(cmd) && !(descr->flags & IW_DESCR_FLAG_NOMAX)) {
		/*
		 * If this is a GET, but not NOMAX, it means that the extra
		 * data is not bounded by userspace, but by max_tokens. Thus
		 * set the length to max_tokens. This matches the extra data
		 * allocation.
		 * The driver should fill it with the number of tokens it
		 * provided, and it may check iwp->length rather than having
		 * knowledge of max_tokens. If the driver doesn't change the
		 * iwp->length, this ioctl just copies back max_token tokens
		 * filled with zeroes. Hopefully the driver isn't claiming
		 * them to be valid data.
		 */
		iwp->length = descr->max_tokens;
	}

	err = handler(dev, info, (union iwreq_data *) iwp, extra);

	iwp->length += essid_compat;

	/* If we have something to return to the user */
	if (!err && IW_IS_GET(cmd)) {
		/* Check if there is enough buffer up there */
		if (user_length < iwp->length) {
			err = -E2BIG;
			goto out;
		}

		if (copy_to_user(iwp->pointer, extra,
				 iwp->length *
				 descr->token_size)) {
			err = -EFAULT;
			goto out;
		}
	}

	/* Generate an event to notify listeners of the change */
	if ((descr->flags & IW_DESCR_FLAG_EVENT) &&
	    ((err == 0) || (err == -EIWCOMMIT))) {
		union iwreq_data *data = (union iwreq_data *) iwp;

		if (descr->flags & IW_DESCR_FLAG_RESTRICT)
			/* If the event is restricted, don't
			 * export the payload.
			 */
			wireless_send_event(dev, cmd, data, NULL);
		else
			wireless_send_event(dev, cmd, data, extra);
	}

out:
	kfree(extra);
	return err;
}