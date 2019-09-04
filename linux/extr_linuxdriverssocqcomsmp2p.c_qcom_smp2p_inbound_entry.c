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
struct smp2p_entry {int /*<<< orphan*/  domain; } ;
struct qcom_smp2p {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int,int /*<<< orphan*/ *,struct smp2p_entry*) ; 
 int /*<<< orphan*/  smp2p_irq_ops ; 

__attribute__((used)) static int qcom_smp2p_inbound_entry(struct qcom_smp2p *smp2p,
				    struct smp2p_entry *entry,
				    struct device_node *node)
{
	entry->domain = irq_domain_add_linear(node, 32, &smp2p_irq_ops, entry);
	if (!entry->domain) {
		dev_err(smp2p->dev, "failed to add irq_domain\n");
		return -ENOMEM;
	}

	return 0;
}