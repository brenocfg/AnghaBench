#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dw_spi_mscc {scalar_t__ syscon; scalar_t__ spi_mst; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_cs; } ;
struct dw_spi_mmio {struct dw_spi_mscc* priv; TYPE_1__ dws; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  MSCC_CPU_SYSTEM_CTRL_GENERAL_CTRL ; 
 int MSCC_IF_SI_OWNER_SIMC ; 
 scalar_t__ MSCC_SPI_MST_SW_MODE ; 
 int /*<<< orphan*/  OCELOT_IF_SI_OWNER_MASK ; 
 int OCELOT_IF_SI_OWNER_OFFSET ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct dw_spi_mscc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_spi_mscc_set_cs ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_update_bits (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ syscon_regmap_lookup_by_compatible (char*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dw_spi_mscc_init(struct platform_device *pdev,
			    struct dw_spi_mmio *dwsmmio)
{
	struct dw_spi_mscc *dwsmscc;
	struct resource *res;

	dwsmscc = devm_kzalloc(&pdev->dev, sizeof(*dwsmscc), GFP_KERNEL);
	if (!dwsmscc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	dwsmscc->spi_mst = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(dwsmscc->spi_mst)) {
		dev_err(&pdev->dev, "SPI_MST region map failed\n");
		return PTR_ERR(dwsmscc->spi_mst);
	}

	dwsmscc->syscon = syscon_regmap_lookup_by_compatible("mscc,ocelot-cpu-syscon");
	if (IS_ERR(dwsmscc->syscon))
		return PTR_ERR(dwsmscc->syscon);

	/* Deassert all CS */
	writel(0, dwsmscc->spi_mst + MSCC_SPI_MST_SW_MODE);

	/* Select the owner of the SI interface */
	regmap_update_bits(dwsmscc->syscon, MSCC_CPU_SYSTEM_CTRL_GENERAL_CTRL,
			   OCELOT_IF_SI_OWNER_MASK,
			   MSCC_IF_SI_OWNER_SIMC << OCELOT_IF_SI_OWNER_OFFSET);

	dwsmmio->dws.set_cs = dw_spi_mscc_set_cs;
	dwsmmio->priv = dwsmscc;

	return 0;
}