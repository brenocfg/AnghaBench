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
struct spmi_pmic_arb {int /*<<< orphan*/  domain; int /*<<< orphan*/  irq; } ;
struct spmi_controller {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct spmi_controller* platform_get_drvdata (struct platform_device*) ; 
 struct spmi_pmic_arb* spmi_controller_get_drvdata (struct spmi_controller*) ; 
 int /*<<< orphan*/  spmi_controller_put (struct spmi_controller*) ; 
 int /*<<< orphan*/  spmi_controller_remove (struct spmi_controller*) ; 

__attribute__((used)) static int spmi_pmic_arb_remove(struct platform_device *pdev)
{
	struct spmi_controller *ctrl = platform_get_drvdata(pdev);
	struct spmi_pmic_arb *pmic_arb = spmi_controller_get_drvdata(ctrl);
	spmi_controller_remove(ctrl);
	irq_set_chained_handler_and_data(pmic_arb->irq, NULL, NULL);
	irq_domain_remove(pmic_arb->domain);
	spmi_controller_put(ctrl);
	return 0;
}