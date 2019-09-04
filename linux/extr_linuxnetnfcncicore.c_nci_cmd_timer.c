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
struct nci_dev {int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  cmd_wq; int /*<<< orphan*/  cmd_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmd_timer ; 
 struct nci_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct nci_dev* ndev ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nci_cmd_timer(struct timer_list *t)
{
	struct nci_dev *ndev = from_timer(ndev, t, cmd_timer);

	atomic_set(&ndev->cmd_cnt, 1);
	queue_work(ndev->cmd_wq, &ndev->cmd_work);
}