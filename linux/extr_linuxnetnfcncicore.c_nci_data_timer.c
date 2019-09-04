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
struct timer_list {int dummy; } ;
struct nci_dev {int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rx_wq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_DATA_EXCHANGE_TO ; 
 int /*<<< orphan*/  data_timer ; 
 struct nci_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct nci_dev* ndev ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nci_data_timer(struct timer_list *t)
{
	struct nci_dev *ndev = from_timer(ndev, t, data_timer);

	set_bit(NCI_DATA_EXCHANGE_TO, &ndev->flags);
	queue_work(ndev->rx_wq, &ndev->rx_work);
}