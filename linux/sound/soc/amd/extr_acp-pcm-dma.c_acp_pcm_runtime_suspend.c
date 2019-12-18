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
struct device {int dummy; } ;
struct audio_drv_data {int /*<<< orphan*/  acp_mmio; } ;

/* Variables and functions */
 int acp_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct audio_drv_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mmACP_EXTERNAL_INTR_ENB ; 

__attribute__((used)) static int acp_pcm_runtime_suspend(struct device *dev)
{
	int status;
	struct audio_drv_data *adata = dev_get_drvdata(dev);

	status = acp_deinit(adata->acp_mmio);
	if (status)
		dev_err(dev, "ACP Deinit failed status:%d\n", status);
	acp_reg_write(0, adata->acp_mmio, mmACP_EXTERNAL_INTR_ENB);
	return 0;
}