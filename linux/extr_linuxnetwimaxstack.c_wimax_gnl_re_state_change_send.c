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
struct wimax_dev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct wimax_dev*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct wimax_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* wimax_dev_to_dev (struct wimax_dev*) ; 
 int /*<<< orphan*/  wimax_gnl_family ; 

__attribute__((used)) static
int wimax_gnl_re_state_change_send(
	struct wimax_dev *wimax_dev, struct sk_buff *report_skb,
	void *header)
{
	int result = 0;
	struct device *dev = wimax_dev_to_dev(wimax_dev);
	d_fnstart(3, dev, "(wimax_dev %p report_skb %p)\n",
		  wimax_dev, report_skb);
	if (report_skb == NULL) {
		result = -ENOMEM;
		goto out;
	}
	genlmsg_end(report_skb, header);
	genlmsg_multicast(&wimax_gnl_family, report_skb, 0, 0, GFP_KERNEL);
out:
	d_fnend(3, dev, "(wimax_dev %p report_skb %p) = %d\n",
		wimax_dev, report_skb, result);
	return result;
}