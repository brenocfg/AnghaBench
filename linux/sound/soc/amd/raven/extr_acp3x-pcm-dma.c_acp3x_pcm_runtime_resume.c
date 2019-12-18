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
struct i2s_dev_data {scalar_t__ acp3x_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int acp3x_init (scalar_t__) ; 
 struct i2s_dev_data* dev_get_drvdata (struct device*) ; 
 scalar_t__ mmACP_EXTERNAL_INTR_ENB ; 
 int /*<<< orphan*/  rv_writel (int,scalar_t__) ; 

__attribute__((used)) static int acp3x_pcm_runtime_resume(struct device *dev)
{
	int status;
	struct i2s_dev_data *adata = dev_get_drvdata(dev);

	status = acp3x_init(adata->acp3x_base);
	if (status)
		return -ENODEV;
	rv_writel(1, adata->acp3x_base + mmACP_EXTERNAL_INTR_ENB);
	return 0;
}