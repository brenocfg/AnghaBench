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
struct snic_tgt {int /*<<< orphan*/  list; int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_BUG_ON (int) ; 
 int /*<<< orphan*/  SNIC_HOST_INFO (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct snic_tgt* dev_to_tgt (struct device*) ; 
 int /*<<< orphan*/  kfree (struct snic_tgt*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snic_tgt_to_shost (struct snic_tgt*) ; 

void
snic_tgt_dev_release(struct device *dev)
{
	struct snic_tgt *tgt = dev_to_tgt(dev);

	SNIC_HOST_INFO(snic_tgt_to_shost(tgt),
		       "Target Device ID %d (%s) Permanently Deleted.\n",
		       tgt->id,
		       dev_name(dev));

	SNIC_BUG_ON(!list_empty(&tgt->list));
	kfree(tgt);
}