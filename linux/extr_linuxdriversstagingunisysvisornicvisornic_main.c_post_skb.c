#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sent_post; int /*<<< orphan*/  sent_post_failed; } ;
struct visornic_devdata {TYPE_5__ chstat; int /*<<< orphan*/  num_rcvbuf_in_iovm; TYPE_4__* dev; int /*<<< orphan*/  incarnation_id; } ;
struct TYPE_6__ {unsigned long pi_off; scalar_t__ pi_len; int /*<<< orphan*/  pi_pfn; } ;
struct TYPE_7__ {TYPE_1__ frag; int /*<<< orphan*/  unique_num; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; TYPE_2__ rcvpost; struct sk_buff* buf; } ;
struct uiscmdrsp {int /*<<< orphan*/  cmdtype; TYPE_3__ net; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_9__ {int /*<<< orphan*/  visorchannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_NET_TYPE ; 
 int EINVAL ; 
 int /*<<< orphan*/  IOCHAN_TO_IOPART ; 
 int /*<<< orphan*/  NET_RCV_POST ; 
 unsigned long PI_PAGE_MASK ; 
 scalar_t__ PI_PAGE_SIZE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 
 int visorchannel_signalinsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uiscmdrsp*) ; 

__attribute__((used)) static int post_skb(struct uiscmdrsp *cmdrsp, struct visornic_devdata *devdata,
		    struct sk_buff *skb)
{
	int err;

	cmdrsp->net.buf = skb;
	cmdrsp->net.rcvpost.frag.pi_pfn = page_to_pfn(virt_to_page(skb->data));
	cmdrsp->net.rcvpost.frag.pi_off =
		(unsigned long)skb->data & PI_PAGE_MASK;
	cmdrsp->net.rcvpost.frag.pi_len = skb->len;
	cmdrsp->net.rcvpost.unique_num = devdata->incarnation_id;

	if ((cmdrsp->net.rcvpost.frag.pi_off + skb->len) > PI_PAGE_SIZE)
		return -EINVAL;

	cmdrsp->net.type = NET_RCV_POST;
	cmdrsp->cmdtype = CMD_NET_TYPE;
	err = visorchannel_signalinsert(devdata->dev->visorchannel,
					IOCHAN_TO_IOPART,
					cmdrsp);
	if (err) {
		devdata->chstat.sent_post_failed++;
		return err;
	}

	atomic_inc(&devdata->num_rcvbuf_in_iovm);
	devdata->chstat.sent_post++;
	return 0;
}