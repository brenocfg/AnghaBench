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
struct wcn36xx {int is_pronto; void* ccu_base; int /*<<< orphan*/  rf_id; void* dxe_base; void* tx_rings_empty_state; int /*<<< orphan*/  tx_rings_empty_state_bit; void* tx_enable_state; int /*<<< orphan*/  tx_enable_state_bit; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  RF_IRIS_WCN3620 ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 void* of_iomap (struct device_node*,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int of_property_match_string (struct device_node*,char*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 void* qcom_smem_state_get (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*) ; 

__attribute__((used)) static int wcn36xx_platform_get_resources(struct wcn36xx *wcn,
					  struct platform_device *pdev)
{
	struct device_node *mmio_node;
	struct device_node *iris_node;
	struct resource *res;
	int index;
	int ret;

	/* Set TX IRQ */
	res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, "tx");
	if (!res) {
		wcn36xx_err("failed to get tx_irq\n");
		return -ENOENT;
	}
	wcn->tx_irq = res->start;

	/* Set RX IRQ */
	res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, "rx");
	if (!res) {
		wcn36xx_err("failed to get rx_irq\n");
		return -ENOENT;
	}
	wcn->rx_irq = res->start;

	/* Acquire SMSM tx enable handle */
	wcn->tx_enable_state = qcom_smem_state_get(&pdev->dev,
			"tx-enable", &wcn->tx_enable_state_bit);
	if (IS_ERR(wcn->tx_enable_state)) {
		wcn36xx_err("failed to get tx-enable state\n");
		return PTR_ERR(wcn->tx_enable_state);
	}

	/* Acquire SMSM tx rings empty handle */
	wcn->tx_rings_empty_state = qcom_smem_state_get(&pdev->dev,
			"tx-rings-empty", &wcn->tx_rings_empty_state_bit);
	if (IS_ERR(wcn->tx_rings_empty_state)) {
		wcn36xx_err("failed to get tx-rings-empty state\n");
		return PTR_ERR(wcn->tx_rings_empty_state);
	}

	mmio_node = of_parse_phandle(pdev->dev.parent->of_node, "qcom,mmio", 0);
	if (!mmio_node) {
		wcn36xx_err("failed to acquire qcom,mmio reference\n");
		return -EINVAL;
	}

	wcn->is_pronto = !!of_device_is_compatible(mmio_node, "qcom,pronto");

	/* Map the CCU memory */
	index = of_property_match_string(mmio_node, "reg-names", "ccu");
	wcn->ccu_base = of_iomap(mmio_node, index);
	if (!wcn->ccu_base) {
		wcn36xx_err("failed to map ccu memory\n");
		ret = -ENOMEM;
		goto put_mmio_node;
	}

	/* Map the DXE memory */
	index = of_property_match_string(mmio_node, "reg-names", "dxe");
	wcn->dxe_base = of_iomap(mmio_node, index);
	if (!wcn->dxe_base) {
		wcn36xx_err("failed to map dxe memory\n");
		ret = -ENOMEM;
		goto unmap_ccu;
	}

	/* External RF module */
	iris_node = of_get_child_by_name(mmio_node, "iris");
	if (iris_node) {
		if (of_device_is_compatible(iris_node, "qcom,wcn3620"))
			wcn->rf_id = RF_IRIS_WCN3620;
		of_node_put(iris_node);
	}

	of_node_put(mmio_node);
	return 0;

unmap_ccu:
	iounmap(wcn->ccu_base);
put_mmio_node:
	of_node_put(mmio_node);
	return ret;
}