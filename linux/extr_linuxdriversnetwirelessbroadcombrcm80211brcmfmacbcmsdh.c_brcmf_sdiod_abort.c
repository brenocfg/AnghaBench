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
struct sdio_func {int /*<<< orphan*/  num; } ;
struct brcmf_sdio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  SDIO_CCCR_ABORT ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_sdiod_func0_wb (struct brcmf_sdio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int brcmf_sdiod_abort(struct brcmf_sdio_dev *sdiodev, struct sdio_func *func)
{
	brcmf_dbg(SDIO, "Enter\n");

	/* Issue abort cmd52 command through F0 */
	brcmf_sdiod_func0_wb(sdiodev, SDIO_CCCR_ABORT, func->num, NULL);

	brcmf_dbg(SDIO, "Exit\n");
	return 0;
}