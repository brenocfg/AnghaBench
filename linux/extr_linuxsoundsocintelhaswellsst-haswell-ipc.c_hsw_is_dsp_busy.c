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
typedef  int u64 ;
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SST_IPCX ; 
 int SST_IPCX_BUSY ; 
 int SST_IPCX_DONE ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hsw_is_dsp_busy(struct sst_dsp *dsp)
{
	u64 ipcx;

	ipcx = sst_dsp_shim_read_unlocked(dsp, SST_IPCX);
	return (ipcx & (SST_IPCX_BUSY | SST_IPCX_DONE));
}