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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct ssb_bus {int /*<<< orphan*/  host_sdio; } ;

/* Variables and functions */
 int SSB_CORE_SIZE ; 
 scalar_t__ SSB_ENUM_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_sdio_dev (struct ssb_bus*) ; 
 int ssb_sdio_set_sbaddr_window (struct ssb_bus*,scalar_t__) ; 

int ssb_sdio_scan_switch_coreidx(struct ssb_bus *bus, u8 coreidx)
{
	u32 sbaddr;
	int error;

	sbaddr = (coreidx * SSB_CORE_SIZE) + SSB_ENUM_BASE;
	sdio_claim_host(bus->host_sdio);
	error = ssb_sdio_set_sbaddr_window(bus, sbaddr);
	sdio_release_host(bus->host_sdio);
	if (error) {
		dev_err(ssb_sdio_dev(bus), "failed to switch to core %u,"
			" error %d\n", coreidx, error);
		goto out;
	}
out:
	return error;
}