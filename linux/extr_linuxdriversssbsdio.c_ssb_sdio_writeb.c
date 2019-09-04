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
typedef  int /*<<< orphan*/  u8 ;
struct ssb_bus {int /*<<< orphan*/  host_sdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int*) ; 
 int /*<<< orphan*/  ssb_sdio_dev (struct ssb_bus*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ssb_sdio_writeb(struct ssb_bus *bus, unsigned int addr, u8 val)
{
	int error = 0;

	sdio_writeb(bus->host_sdio, val, addr, &error);
	if (unlikely(error)) {
		dev_dbg(ssb_sdio_dev(bus), "%08X <- %02x, error %d\n",
			addr, val, error);
	}

	return error;
}