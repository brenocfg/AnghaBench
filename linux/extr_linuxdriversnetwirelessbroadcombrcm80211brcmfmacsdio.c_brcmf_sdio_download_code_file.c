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
typedef  int /*<<< orphan*/  u8 ;
struct firmware {scalar_t__ size; scalar_t__ data; } ;
struct brcmf_sdio {TYPE_1__* ci; int /*<<< orphan*/  sdiodev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rambase; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdio_verifymemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int brcmf_sdiod_ramrw (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int brcmf_sdio_download_code_file(struct brcmf_sdio *bus,
					 const struct firmware *fw)
{
	int err;

	brcmf_dbg(TRACE, "Enter\n");

	err = brcmf_sdiod_ramrw(bus->sdiodev, true, bus->ci->rambase,
				(u8 *)fw->data, fw->size);
	if (err)
		brcmf_err("error %d on writing %d membytes at 0x%08x\n",
			  err, (int)fw->size, bus->ci->rambase);
	else if (!brcmf_sdio_verifymemory(bus->sdiodev, bus->ci->rambase,
					  (u8 *)fw->data, fw->size))
		err = -EIO;

	return err;
}