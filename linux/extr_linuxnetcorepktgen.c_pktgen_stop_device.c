#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pktgen_dev {int /*<<< orphan*/  stopped_at; int /*<<< orphan*/ * skb; scalar_t__ running; int /*<<< orphan*/  odevname; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_results (struct pktgen_dev*,int) ; 
 TYPE_1__* skb_shinfo (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pktgen_stop_device(struct pktgen_dev *pkt_dev)
{
	int nr_frags = pkt_dev->skb ? skb_shinfo(pkt_dev->skb)->nr_frags : -1;

	if (!pkt_dev->running) {
		pr_warn("interface: %s is already stopped\n",
			pkt_dev->odevname);
		return -EINVAL;
	}

	pkt_dev->running = 0;
	kfree_skb(pkt_dev->skb);
	pkt_dev->skb = NULL;
	pkt_dev->stopped_at = ktime_get();

	show_results(pkt_dev, nr_frags);

	return 0;
}