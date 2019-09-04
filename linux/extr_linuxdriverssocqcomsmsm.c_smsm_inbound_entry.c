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
struct smsm_entry {int /*<<< orphan*/  domain; } ;
struct qcom_smsm {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int,int /*<<< orphan*/ *,struct smsm_entry*) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsm_intr ; 
 int /*<<< orphan*/  smsm_irq_ops ; 

__attribute__((used)) static int smsm_inbound_entry(struct qcom_smsm *smsm,
			      struct smsm_entry *entry,
			      struct device_node *node)
{
	int ret;
	int irq;

	irq = irq_of_parse_and_map(node, 0);
	if (!irq) {
		dev_err(smsm->dev, "failed to parse smsm interrupt\n");
		return -EINVAL;
	}

	ret = devm_request_threaded_irq(smsm->dev, irq,
					NULL, smsm_intr,
					IRQF_ONESHOT,
					"smsm", (void *)entry);
	if (ret) {
		dev_err(smsm->dev, "failed to request interrupt\n");
		return ret;
	}

	entry->domain = irq_domain_add_linear(node, 32, &smsm_irq_ops, entry);
	if (!entry->domain) {
		dev_err(smsm->dev, "failed to add irq_domain\n");
		return -ENOMEM;
	}

	return 0;
}