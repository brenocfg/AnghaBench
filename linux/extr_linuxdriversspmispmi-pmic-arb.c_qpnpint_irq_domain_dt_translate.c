#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  void* u16 ;
struct spmi_pmic_arb {void* max_apid; void* min_apid; TYPE_2__* spmic; TYPE_1__* ver_ops; } ;
struct irq_domain {struct spmi_pmic_arb* host_data; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* ppid_to_apid ) (struct spmi_pmic_arb*,void*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int const IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int const,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int const,int const,int const,int) ; 
 struct device_node* irq_domain_get_of_node (struct irq_domain*) ; 
 unsigned long spec_to_hwirq (int const,int const,int const,void*) ; 
 int stub1 (struct spmi_pmic_arb*,void*) ; 

__attribute__((used)) static int qpnpint_irq_domain_dt_translate(struct irq_domain *d,
					   struct device_node *controller,
					   const u32 *intspec,
					   unsigned int intsize,
					   unsigned long *out_hwirq,
					   unsigned int *out_type)
{
	struct spmi_pmic_arb *pmic_arb = d->host_data;
	u16 apid, ppid;
	int rc;

	dev_dbg(&pmic_arb->spmic->dev, "intspec[0] 0x%1x intspec[1] 0x%02x intspec[2] 0x%02x\n",
		intspec[0], intspec[1], intspec[2]);

	if (irq_domain_get_of_node(d) != controller)
		return -EINVAL;
	if (intsize != 4)
		return -EINVAL;
	if (intspec[0] > 0xF || intspec[1] > 0xFF || intspec[2] > 0x7)
		return -EINVAL;

	ppid = intspec[0] << 8 | intspec[1];
	rc = pmic_arb->ver_ops->ppid_to_apid(pmic_arb, ppid);
	if (rc < 0) {
		dev_err(&pmic_arb->spmic->dev, "failed to xlate sid = %#x, periph = %#x, irq = %u rc = %d\n",
		intspec[0], intspec[1], intspec[2], rc);
		return rc;
	}

	apid = rc;
	/* Keep track of {max,min}_apid for bounding search during interrupt */
	if (apid > pmic_arb->max_apid)
		pmic_arb->max_apid = apid;
	if (apid < pmic_arb->min_apid)
		pmic_arb->min_apid = apid;

	*out_hwirq = spec_to_hwirq(intspec[0], intspec[1], intspec[2], apid);
	*out_type  = intspec[3] & IRQ_TYPE_SENSE_MASK;

	dev_dbg(&pmic_arb->spmic->dev, "out_hwirq = %lu\n", *out_hwirq);

	return 0;
}