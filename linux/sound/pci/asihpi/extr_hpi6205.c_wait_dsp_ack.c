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
struct hpi_hw_obj {struct bus_master_interface* p_interface_buffer; } ;
struct bus_master_interface {int dsp_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpios_delay_micro_seconds (int) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static int wait_dsp_ack(struct hpi_hw_obj *phw, int state, int timeout_us)
{
	struct bus_master_interface *interface = phw->p_interface_buffer;
	int t = timeout_us / 4;

	rmb();	/* ensure interface->dsp_ack is up to date */
	while ((interface->dsp_ack != state) && --t) {
		hpios_delay_micro_seconds(4);
		rmb();	/* DSP changes dsp_ack by DMA */
	}

	/*HPI_DEBUG_LOG(VERBOSE, "Spun %d for %d\n", timeout_us/4-t, state); */
	return t * 4;
}