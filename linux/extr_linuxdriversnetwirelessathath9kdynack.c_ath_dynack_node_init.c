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
typedef  int u32 ;
struct ath_node {int ackto; int /*<<< orphan*/  list; } ;
struct ath_dynack {int /*<<< orphan*/  qlock; int /*<<< orphan*/  nodes; } ;
struct ath_hw {struct ath_dynack dynack; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ath_dynack_node_init(struct ath_hw *ah, struct ath_node *an)
{
	/* ackto = slottime + sifs + air delay */
	u32 ackto = 9 + 16 + 64;
	struct ath_dynack *da = &ah->dynack;

	an->ackto = ackto;

	spin_lock(&da->qlock);
	list_add_tail(&an->list, &da->nodes);
	spin_unlock(&da->qlock);
}