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
struct TYPE_3__ {int length; } ;
union iwreq_data {TYPE_1__ data; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_ioctl_description {size_t header_type; int max_tokens; int min_tokens; int token_size; } ;
struct iw_event {int len; unsigned int cmd; char u; } ;
struct TYPE_4__ {int /*<<< orphan*/  wext_nlevents; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IFLA_WIRELESS ; 
 unsigned int IW_EVENT_IDX (unsigned int) ; 
 int IW_EV_LCP_LEN ; 
 int IW_EV_POINT_OFF ; 
 size_t IW_HEADER_TYPE_POINT ; 
 unsigned int IW_IOCTL_IDX (unsigned int) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 unsigned int SIOCGIWSCAN ; 
 unsigned int SIOCIWLAST ; 
 scalar_t__ WARN_ON (int) ; 
 TYPE_2__* dev_net (struct net_device*) ; 
 int* event_type_size ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct iw_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,unsigned int,...) ; 
 struct iw_event* nla_data (struct nlattr*) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlmsghdr* rtnetlink_ifinfo_prep (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct iw_ioctl_description* standard_event ; 
 unsigned int standard_event_num ; 
 struct iw_ioctl_description* standard_ioctl ; 
 unsigned int standard_ioctl_num ; 
 int /*<<< orphan*/  wireless_nlevent_work ; 

void wireless_send_event(struct net_device *	dev,
			 unsigned int		cmd,
			 union iwreq_data *	wrqu,
			 const char *		extra)
{
	const struct iw_ioctl_description *	descr = NULL;
	int extra_len = 0;
	struct iw_event  *event;		/* Mallocated whole event */
	int event_len;				/* Its size */
	int hdr_len;				/* Size of the event header */
	int wrqu_off = 0;			/* Offset in wrqu */
	/* Don't "optimise" the following variable, it will crash */
	unsigned int	cmd_index;		/* *MUST* be unsigned */
	struct sk_buff *skb;
	struct nlmsghdr *nlh;
	struct nlattr *nla;
#ifdef CONFIG_COMPAT
	struct __compat_iw_event *compat_event;
	struct compat_iw_point compat_wrqu;
	struct sk_buff *compskb;
#endif

	/*
	 * Nothing in the kernel sends scan events with data, be safe.
	 * This is necessary because we cannot fix up scan event data
	 * for compat, due to being contained in 'extra', but normally
	 * applications are required to retrieve the scan data anyway
	 * and no data is included in the event, this codifies that
	 * practice.
	 */
	if (WARN_ON(cmd == SIOCGIWSCAN && extra))
		extra = NULL;

	/* Get the description of the Event */
	if (cmd <= SIOCIWLAST) {
		cmd_index = IW_IOCTL_IDX(cmd);
		if (cmd_index < standard_ioctl_num)
			descr = &(standard_ioctl[cmd_index]);
	} else {
		cmd_index = IW_EVENT_IDX(cmd);
		if (cmd_index < standard_event_num)
			descr = &(standard_event[cmd_index]);
	}
	/* Don't accept unknown events */
	if (descr == NULL) {
		/* Note : we don't return an error to the driver, because
		 * the driver would not know what to do about it. It can't
		 * return an error to the user, because the event is not
		 * initiated by a user request.
		 * The best the driver could do is to log an error message.
		 * We will do it ourselves instead...
		 */
		netdev_err(dev, "(WE) : Invalid/Unknown Wireless Event (0x%04X)\n",
			   cmd);
		return;
	}

	/* Check extra parameters and set extra_len */
	if (descr->header_type == IW_HEADER_TYPE_POINT) {
		/* Check if number of token fits within bounds */
		if (wrqu->data.length > descr->max_tokens) {
			netdev_err(dev, "(WE) : Wireless Event (cmd=0x%04X) too big (%d)\n",
				   cmd, wrqu->data.length);
			return;
		}
		if (wrqu->data.length < descr->min_tokens) {
			netdev_err(dev, "(WE) : Wireless Event (cmd=0x%04X) too small (%d)\n",
				   cmd, wrqu->data.length);
			return;
		}
		/* Calculate extra_len - extra is NULL for restricted events */
		if (extra != NULL)
			extra_len = wrqu->data.length * descr->token_size;
		/* Always at an offset in wrqu */
		wrqu_off = IW_EV_POINT_OFF;
	}

	/* Total length of the event */
	hdr_len = event_type_size[descr->header_type];
	event_len = hdr_len + extra_len;

	/*
	 * The problem for 64/32 bit.
	 *
	 * On 64-bit, a regular event is laid out as follows:
	 *      |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
	 *      | event.len | event.cmd |     p a d d i n g     |
	 *      | wrqu data ... (with the correct size)         |
	 *
	 * This padding exists because we manipulate event->u,
	 * and 'event' is not packed.
	 *
	 * An iw_point event is laid out like this instead:
	 *      |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
	 *      | event.len | event.cmd |     p a d d i n g     |
	 *      | iwpnt.len | iwpnt.flg |     p a d d i n g     |
	 *      | extra data  ...
	 *
	 * The second padding exists because struct iw_point is extended,
	 * but this depends on the platform...
	 *
	 * On 32-bit, all the padding shouldn't be there.
	 */

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	if (!skb)
		return;

	/* Send via the RtNetlink event channel */
	nlh = rtnetlink_ifinfo_prep(dev, skb);
	if (WARN_ON(!nlh)) {
		kfree_skb(skb);
		return;
	}

	/* Add the wireless events in the netlink packet */
	nla = nla_reserve(skb, IFLA_WIRELESS, event_len);
	if (!nla) {
		kfree_skb(skb);
		return;
	}
	event = nla_data(nla);

	/* Fill event - first clear to avoid data leaking */
	memset(event, 0, hdr_len);
	event->len = event_len;
	event->cmd = cmd;
	memcpy(&event->u, ((char *) wrqu) + wrqu_off, hdr_len - IW_EV_LCP_LEN);
	if (extra_len)
		memcpy(((char *) event) + hdr_len, extra, extra_len);

	nlmsg_end(skb, nlh);
#ifdef CONFIG_COMPAT
	hdr_len = compat_event_type_size[descr->header_type];
	event_len = hdr_len + extra_len;

	compskb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	if (!compskb) {
		kfree_skb(skb);
		return;
	}

	/* Send via the RtNetlink event channel */
	nlh = rtnetlink_ifinfo_prep(dev, compskb);
	if (WARN_ON(!nlh)) {
		kfree_skb(skb);
		kfree_skb(compskb);
		return;
	}

	/* Add the wireless events in the netlink packet */
	nla = nla_reserve(compskb, IFLA_WIRELESS, event_len);
	if (!nla) {
		kfree_skb(skb);
		kfree_skb(compskb);
		return;
	}
	compat_event = nla_data(nla);

	compat_event->len = event_len;
	compat_event->cmd = cmd;
	if (descr->header_type == IW_HEADER_TYPE_POINT) {
		compat_wrqu.length = wrqu->data.length;
		compat_wrqu.flags = wrqu->data.flags;
		memcpy(&compat_event->pointer,
			((char *) &compat_wrqu) + IW_EV_COMPAT_POINT_OFF,
			hdr_len - IW_EV_COMPAT_LCP_LEN);
		if (extra_len)
			memcpy(((char *) compat_event) + hdr_len,
				extra, extra_len);
	} else {
		/* extra_len must be zero, so no if (extra) needed */
		memcpy(&compat_event->pointer, wrqu,
			hdr_len - IW_EV_COMPAT_LCP_LEN);
	}

	nlmsg_end(compskb, nlh);

	skb_shinfo(skb)->frag_list = compskb;
#endif
	skb_queue_tail(&dev_net(dev)->wext_nlevents, skb);
	schedule_work(&wireless_nlevent_work);
}