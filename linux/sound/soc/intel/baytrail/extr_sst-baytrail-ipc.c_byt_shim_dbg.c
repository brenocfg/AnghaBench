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
typedef  int /*<<< orphan*/  u64 ;
struct sst_generic_ipc {int /*<<< orphan*/  dev; struct sst_dsp* dsp; } ;
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_IMRX ; 
 int /*<<< orphan*/  SST_IPCD ; 
 int /*<<< orphan*/  SST_IPCX ; 
 int /*<<< orphan*/  SST_ISRX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_read64_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void byt_shim_dbg(struct sst_generic_ipc *ipc, const char *text)
{
	struct sst_dsp *sst = ipc->dsp;
	u64 isr, ipcd, imrx, ipcx;

	ipcx = sst_dsp_shim_read64_unlocked(sst, SST_IPCX);
	isr = sst_dsp_shim_read64_unlocked(sst, SST_ISRX);
	ipcd = sst_dsp_shim_read64_unlocked(sst, SST_IPCD);
	imrx = sst_dsp_shim_read64_unlocked(sst, SST_IMRX);

	dev_err(ipc->dev,
		"ipc: --%s-- ipcx 0x%llx isr 0x%llx ipcd 0x%llx imrx 0x%llx\n",
		text, ipcx, isr, ipcd, imrx);
}