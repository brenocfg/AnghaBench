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
typedef  int uint32_t ;

/* Variables and functions */
 int HDA_DSP_IPC_PURGE_FW ; 

__attribute__((used)) static bool hda_dsp_ipc_is_sof(uint32_t msg)
{
	return (msg & (HDA_DSP_IPC_PURGE_FW | 0xf << 9)) != msg ||
		(msg & HDA_DSP_IPC_PURGE_FW) != HDA_DSP_IPC_PURGE_FW;
}