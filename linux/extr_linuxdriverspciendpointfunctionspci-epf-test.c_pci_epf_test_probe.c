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
struct pci_epf_test_data {int test_reg_bar; int linkup_notifier; } ;
struct pci_epf_test {int test_reg_bar; int linkup_notifier; int /*<<< orphan*/  cmd_handler; struct pci_epf* epf; } ;
struct pci_epf_device_id {scalar_t__ driver_data; } ;
struct device {int dummy; } ;
struct pci_epf {int /*<<< orphan*/ * header; struct device dev; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int BAR_0 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pci_epf_test* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epf_set_drvdata (struct pci_epf*,struct pci_epf_test*) ; 
 struct pci_epf_device_id* pci_epf_match_device (int /*<<< orphan*/ ,struct pci_epf*) ; 
 int /*<<< orphan*/  pci_epf_test_cmd_handler ; 
 int /*<<< orphan*/  pci_epf_test_ids ; 
 int /*<<< orphan*/  test_header ; 

__attribute__((used)) static int pci_epf_test_probe(struct pci_epf *epf)
{
	struct pci_epf_test *epf_test;
	struct device *dev = &epf->dev;
	const struct pci_epf_device_id *match;
	struct pci_epf_test_data *data;
	enum pci_barno test_reg_bar = BAR_0;
	bool linkup_notifier = true;

	match = pci_epf_match_device(pci_epf_test_ids, epf);
	data = (struct pci_epf_test_data *)match->driver_data;
	if (data) {
		test_reg_bar = data->test_reg_bar;
		linkup_notifier = data->linkup_notifier;
	}

	epf_test = devm_kzalloc(dev, sizeof(*epf_test), GFP_KERNEL);
	if (!epf_test)
		return -ENOMEM;

	epf->header = &test_header;
	epf_test->epf = epf;
	epf_test->test_reg_bar = test_reg_bar;
	epf_test->linkup_notifier = linkup_notifier;

	INIT_DELAYED_WORK(&epf_test->cmd_handler, pci_epf_test_cmd_handler);

	epf_set_drvdata(epf, epf_test);
	return 0;
}