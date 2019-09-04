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
struct hpi_hw_obj {int /*<<< orphan*/  prHDCR; struct bus_master_interface* p_interface_buffer; } ;
struct bus_master_interface {int host_cmd; } ;

/* Variables and functions */
 scalar_t__ C6205_HDCR_DSPINT ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void send_dsp_command(struct hpi_hw_obj *phw, int cmd)
{
	struct bus_master_interface *interface = phw->p_interface_buffer;
	u32 r;

	interface->host_cmd = cmd;
	wmb();	/* DSP gets state by DMA, make sure it is written to memory */
	/* before we interrupt the DSP */
	r = ioread32(phw->prHDCR);
	r |= (u32)C6205_HDCR_DSPINT;
	iowrite32(r, phw->prHDCR);
	r &= ~(u32)C6205_HDCR_DSPINT;
	iowrite32(r, phw->prHDCR);
}