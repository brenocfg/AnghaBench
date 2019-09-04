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
struct _sas_node {int /*<<< orphan*/  list; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_node_lock; int /*<<< orphan*/  sas_expander_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
_scsih_expander_node_add(struct MPT3SAS_ADAPTER *ioc,
	struct _sas_node *sas_expander)
{
	unsigned long flags;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	list_add_tail(&sas_expander->list, &ioc->sas_expander_list);
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
}