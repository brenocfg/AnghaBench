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
struct sst_pdata {struct sst_byt* dsp; } ;
struct sst_byt {int /*<<< orphan*/  ipc; int /*<<< orphan*/  dsp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sst_dsp_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_fw_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_ipc_fini (int /*<<< orphan*/ *) ; 

void sst_byt_dsp_free(struct device *dev, struct sst_pdata *pdata)
{
	struct sst_byt *byt = pdata->dsp;

	sst_dsp_reset(byt->dsp);
	sst_fw_free_all(byt->dsp);
	sst_dsp_free(byt->dsp);
	sst_ipc_fini(&byt->ipc);
}