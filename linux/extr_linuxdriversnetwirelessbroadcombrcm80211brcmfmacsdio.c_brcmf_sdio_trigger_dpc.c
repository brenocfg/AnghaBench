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
struct brcmf_sdio {int dpc_triggered; int /*<<< orphan*/  datawork; int /*<<< orphan*/  brcmf_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void brcmf_sdio_trigger_dpc(struct brcmf_sdio *bus)
{
	if (!bus->dpc_triggered) {
		bus->dpc_triggered = true;
		queue_work(bus->brcmf_wq, &bus->datawork);
	}
}