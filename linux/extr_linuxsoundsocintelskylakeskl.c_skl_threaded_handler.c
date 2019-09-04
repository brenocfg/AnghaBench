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
struct hdac_bus {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTSTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  skl_stream_update ; 
 int /*<<< orphan*/  snd_hdac_bus_handle_stream_irq (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_readl (struct hdac_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t skl_threaded_handler(int irq, void *dev_id)
{
	struct hdac_bus *bus = dev_id;
	u32 status;

	status = snd_hdac_chip_readl(bus, INTSTS);

	snd_hdac_bus_handle_stream_irq(bus, status, skl_stream_update);

	return IRQ_HANDLED;
}