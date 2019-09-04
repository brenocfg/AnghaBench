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

/* Variables and functions */
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_sdmmc_driver ; 
 int /*<<< orphan*/  sdio_unregister_driver (int /*<<< orphan*/ *) ; 

void brcmf_sdio_exit(void)
{
	brcmf_dbg(SDIO, "Enter\n");

	sdio_unregister_driver(&brcmf_sdmmc_driver);
}