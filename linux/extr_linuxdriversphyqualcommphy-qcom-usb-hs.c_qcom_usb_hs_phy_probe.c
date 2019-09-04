#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct ulpi {TYPE_2__ dev; } ;
struct reset_control {int dummy; } ;
typedef  struct reset_control regulator ;
struct TYPE_11__ {int /*<<< orphan*/  notifier_call; } ;
struct qcom_usb_hs_phy {struct reset_control* phy; TYPE_1__ vbus_notify; struct reset_control* vbus_edev; struct reset_control* reset; struct reset_control* v3p3; struct reset_control* v1p8; struct reset_control* sleep_clk; struct reset_control* ref_clk; TYPE_8__* init_seq; struct ulpi* ulpi; } ;
struct phy_provider {int dummy; } ;
typedef  struct reset_control clk ;
struct TYPE_13__ {scalar_t__ val; scalar_t__ addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 struct reset_control* devm_clk_get (TYPE_2__*,char*) ; 
 TYPE_8__* devm_kmalloc_array (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 struct qcom_usb_hs_phy* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct reset_control* devm_phy_create (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct reset_control* devm_regulator_get (TYPE_2__*,char*) ; 
 struct reset_control* devm_reset_control_get (TYPE_2__*,char*) ; 
 struct reset_control* extcon_get_edev_by_phandle (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int of_property_count_u8_elems (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u8_array (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct reset_control*,struct qcom_usb_hs_phy*) ; 
 int /*<<< orphan*/  qcom_usb_hs_phy_ops ; 
 int /*<<< orphan*/  qcom_usb_hs_phy_vbus_notifier ; 
 int /*<<< orphan*/  ulpi_set_drvdata (struct ulpi*,struct qcom_usb_hs_phy*) ; 

__attribute__((used)) static int qcom_usb_hs_phy_probe(struct ulpi *ulpi)
{
	struct qcom_usb_hs_phy *uphy;
	struct phy_provider *p;
	struct clk *clk;
	struct regulator *reg;
	struct reset_control *reset;
	int size;
	int ret;

	uphy = devm_kzalloc(&ulpi->dev, sizeof(*uphy), GFP_KERNEL);
	if (!uphy)
		return -ENOMEM;
	ulpi_set_drvdata(ulpi, uphy);
	uphy->ulpi = ulpi;

	size = of_property_count_u8_elems(ulpi->dev.of_node, "qcom,init-seq");
	if (size < 0)
		size = 0;
	uphy->init_seq = devm_kmalloc_array(&ulpi->dev, (size / 2) + 1,
					   sizeof(*uphy->init_seq), GFP_KERNEL);
	if (!uphy->init_seq)
		return -ENOMEM;
	ret = of_property_read_u8_array(ulpi->dev.of_node, "qcom,init-seq",
					(u8 *)uphy->init_seq, size);
	if (ret && size)
		return ret;
	/* NUL terminate */
	uphy->init_seq[size / 2].addr = uphy->init_seq[size / 2].val = 0;

	uphy->ref_clk = clk = devm_clk_get(&ulpi->dev, "ref");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	uphy->sleep_clk = clk = devm_clk_get(&ulpi->dev, "sleep");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	uphy->v1p8 = reg = devm_regulator_get(&ulpi->dev, "v1p8");
	if (IS_ERR(reg))
		return PTR_ERR(reg);

	uphy->v3p3 = reg = devm_regulator_get(&ulpi->dev, "v3p3");
	if (IS_ERR(reg))
		return PTR_ERR(reg);

	uphy->reset = reset = devm_reset_control_get(&ulpi->dev, "por");
	if (IS_ERR(reset)) {
		if (PTR_ERR(reset) == -EPROBE_DEFER)
			return PTR_ERR(reset);
		uphy->reset = NULL;
	}

	uphy->phy = devm_phy_create(&ulpi->dev, ulpi->dev.of_node,
				    &qcom_usb_hs_phy_ops);
	if (IS_ERR(uphy->phy))
		return PTR_ERR(uphy->phy);

	uphy->vbus_edev = extcon_get_edev_by_phandle(&ulpi->dev, 0);
	if (IS_ERR(uphy->vbus_edev)) {
		if (PTR_ERR(uphy->vbus_edev) != -ENODEV)
			return PTR_ERR(uphy->vbus_edev);
		uphy->vbus_edev = NULL;
	}

	uphy->vbus_notify.notifier_call = qcom_usb_hs_phy_vbus_notifier;
	phy_set_drvdata(uphy->phy, uphy);

	p = devm_of_phy_provider_register(&ulpi->dev, of_phy_simple_xlate);
	return PTR_ERR_OR_ZERO(p);
}