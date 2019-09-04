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
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_RDEV (struct qeth_card*) ; 
 int __qeth_issue_next_read (struct qeth_card*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_issue_next_read(struct qeth_card *card)
{
	int ret;

	spin_lock_irq(get_ccwdev_lock(CARD_RDEV(card)));
	ret = __qeth_issue_next_read(card);
	spin_unlock_irq(get_ccwdev_lock(CARD_RDEV(card)));

	return ret;
}