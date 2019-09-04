#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct brcmf_sdio {int /*<<< orphan*/  sdiodev; TYPE_1__* ci; } ;
struct TYPE_2__ {int ramsize; int rambase; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,int,int,int) ; 
 int /*<<< orphan*/  brcmf_sdio_verifymemory (int /*<<< orphan*/ ,int,void*,int) ; 
 int brcmf_sdiod_ramrw (int /*<<< orphan*/ ,int,int,void*,int) ; 

__attribute__((used)) static int brcmf_sdio_download_nvram(struct brcmf_sdio *bus,
				     void *vars, u32 varsz)
{
	int address;
	int err;

	brcmf_dbg(TRACE, "Enter\n");

	address = bus->ci->ramsize - varsz + bus->ci->rambase;
	err = brcmf_sdiod_ramrw(bus->sdiodev, true, address, vars, varsz);
	if (err)
		brcmf_err("error %d on writing %d nvram bytes at 0x%08x\n",
			  err, varsz, address);
	else if (!brcmf_sdio_verifymemory(bus->sdiodev, address, vars, varsz))
		err = -EIO;

	return err;
}