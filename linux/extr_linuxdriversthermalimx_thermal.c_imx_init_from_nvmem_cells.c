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
typedef  int /*<<< orphan*/  u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int imx_init_calib (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_init_temp_grade (struct platform_device*,int /*<<< orphan*/ ) ; 
 int nvmem_cell_read_u32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_init_from_nvmem_cells(struct platform_device *pdev)
{
	int ret;
	u32 val;

	ret = nvmem_cell_read_u32(&pdev->dev, "calib", &val);
	if (ret)
		return ret;

	ret = imx_init_calib(pdev, val);
	if (ret)
		return ret;

	ret = nvmem_cell_read_u32(&pdev->dev, "temp_grade", &val);
	if (ret)
		return ret;
	imx_init_temp_grade(pdev, val);

	return 0;
}