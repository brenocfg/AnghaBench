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
struct uprobe_consumer {int dummy; } ;
struct uprobe {int /*<<< orphan*/  consumers; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  consumer_del (struct uprobe*,struct uprobe_consumer*) ; 
 int /*<<< orphan*/  delete_uprobe (struct uprobe*) ; 
 int register_for_each_vma (struct uprobe*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__uprobe_unregister(struct uprobe *uprobe, struct uprobe_consumer *uc)
{
	int err;

	if (WARN_ON(!consumer_del(uprobe, uc)))
		return;

	err = register_for_each_vma(uprobe, NULL);
	/* TODO : cant unregister? schedule a worker thread */
	if (!uprobe->consumers && !err)
		delete_uprobe(uprobe);
}