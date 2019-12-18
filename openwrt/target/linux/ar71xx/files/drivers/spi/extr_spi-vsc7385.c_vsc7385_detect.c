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
struct vsc7385 {TYPE_1__* pdata; struct spi_device* spi; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) () ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_SYSTEM ; 
 int /*<<< orphan*/  VSC73XX_ICPU_CHIPID ; 
#define  VSC73XX_ICPU_CHIPID_ID_7385 129 
#define  VSC73XX_ICPU_CHIPID_ID_7395 128 
 int VSC73XX_ICPU_CHIPID_ID_MASK ; 
 int VSC73XX_ICPU_CHIPID_ID_SHIFT ; 
 int VSC73XX_ICPU_CHIPID_REV_MASK ; 
 int VSC73XX_ICPU_CHIPID_REV_SHIFT ; 
 int /*<<< orphan*/  VSC73XX_ICPU_MBOX_VAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int vsc7385_read (struct vsc7385*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int vsc7385_detect(struct vsc7385 *vsc)
{
	struct spi_device *spi = vsc->spi;
	u32 t;
	u32 id;
	u32 rev;
	int err;

	err = vsc7385_read(vsc, VSC73XX_BLOCK_SYSTEM, 0,
				VSC73XX_ICPU_MBOX_VAL, &t);
	if (err) {
		dev_err(&spi->dev, "unable to read mailbox, err=%d\n", err);
		return err;
	}

	if (t == 0xffffffff) {
		dev_dbg(&spi->dev, "assert chip reset\n");
		if (vsc->pdata->reset)
			vsc->pdata->reset();

	}

	err = vsc7385_read(vsc, VSC73XX_BLOCK_SYSTEM, 0,
				VSC73XX_ICPU_CHIPID, &t);
	if (err) {
		dev_err(&spi->dev, "unable to read chip id, err=%d\n", err);
		return err;
	}

	id = (t >> VSC73XX_ICPU_CHIPID_ID_SHIFT) & VSC73XX_ICPU_CHIPID_ID_MASK;
	switch (id) {
	case VSC73XX_ICPU_CHIPID_ID_7385:
	case VSC73XX_ICPU_CHIPID_ID_7395:
		break;
	default:
		dev_err(&spi->dev, "unsupported chip, id=%04x\n", id);
		return -ENODEV;
	}

	rev = (t >> VSC73XX_ICPU_CHIPID_REV_SHIFT) &
	      VSC73XX_ICPU_CHIPID_REV_MASK;
	dev_info(&spi->dev, "VSC%04X (rev. %d) switch found\n", id, rev);

	return 0;
}