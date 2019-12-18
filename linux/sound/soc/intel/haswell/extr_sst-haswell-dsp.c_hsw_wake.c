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
struct sst_dsp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int hsw_set_dsp_D0 (struct sst_dsp*) ; 

__attribute__((used)) static int hsw_wake(struct sst_dsp *sst)
{
	int ret;

	dev_dbg(sst->dev, "HSW_PM dsp runtime resume\n");

	ret = hsw_set_dsp_D0(sst);
	if (ret < 0)
		return ret;

	dev_dbg(sst->dev, "HSW_PM dsp runtime resume exit\n");

	return 0;
}