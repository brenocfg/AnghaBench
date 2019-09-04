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
typedef  int u32 ;
struct device {int dummy; } ;
struct advk_pcie {TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIO_ADDR_LS ; 
#define  PIO_COMPLETION_STATUS_CA 130 
#define  PIO_COMPLETION_STATUS_CRS 129 
 int PIO_COMPLETION_STATUS_MASK ; 
 int PIO_COMPLETION_STATUS_SHIFT ; 
#define  PIO_COMPLETION_STATUS_UR 128 
 int PIO_NON_POSTED_REQ ; 
 int /*<<< orphan*/  PIO_STAT ; 
 int advk_readl (struct advk_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,char*,int,int) ; 

__attribute__((used)) static void advk_pcie_check_pio_status(struct advk_pcie *pcie)
{
	struct device *dev = &pcie->pdev->dev;
	u32 reg;
	unsigned int status;
	char *strcomp_status, *str_posted;

	reg = advk_readl(pcie, PIO_STAT);
	status = (reg & PIO_COMPLETION_STATUS_MASK) >>
		PIO_COMPLETION_STATUS_SHIFT;

	if (!status)
		return;

	switch (status) {
	case PIO_COMPLETION_STATUS_UR:
		strcomp_status = "UR";
		break;
	case PIO_COMPLETION_STATUS_CRS:
		strcomp_status = "CRS";
		break;
	case PIO_COMPLETION_STATUS_CA:
		strcomp_status = "CA";
		break;
	default:
		strcomp_status = "Unknown";
		break;
	}

	if (reg & PIO_NON_POSTED_REQ)
		str_posted = "Non-posted";
	else
		str_posted = "Posted";

	dev_err(dev, "%s PIO Response Status: %s, %#x @ %#x\n",
		str_posted, strcomp_status, reg, advk_readl(pcie, PIO_ADDR_LS));
}