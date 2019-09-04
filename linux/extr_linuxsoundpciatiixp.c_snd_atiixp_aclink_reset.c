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
struct atiixp {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATI_REG_CMD_ACLINK_ACTIVE ; 
 int ATI_REG_CMD_AC_RESET ; 
 int ATI_REG_CMD_AC_SOFT_RESET ; 
 int ATI_REG_CMD_AC_SYNC ; 
 int ATI_REG_CMD_POWERDOWN ; 
 int /*<<< orphan*/  CMD ; 
 int atiixp_read (struct atiixp*,int /*<<< orphan*/ ) ; 
 scalar_t__ atiixp_update (struct atiixp*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_atiixp_aclink_reset(struct atiixp *chip)
{
	int timeout;

	/* reset powerdoewn */
	if (atiixp_update(chip, CMD, ATI_REG_CMD_POWERDOWN, 0))
		udelay(10);

	/* perform a software reset */
	atiixp_update(chip, CMD, ATI_REG_CMD_AC_SOFT_RESET, ATI_REG_CMD_AC_SOFT_RESET);
	atiixp_read(chip, CMD);
	udelay(10);
	atiixp_update(chip, CMD, ATI_REG_CMD_AC_SOFT_RESET, 0);
    
	timeout = 10;
	while (! (atiixp_read(chip, CMD) & ATI_REG_CMD_ACLINK_ACTIVE)) {
		/* do a hard reset */
		atiixp_update(chip, CMD, ATI_REG_CMD_AC_SYNC|ATI_REG_CMD_AC_RESET,
			      ATI_REG_CMD_AC_SYNC);
		atiixp_read(chip, CMD);
		mdelay(1);
		atiixp_update(chip, CMD, ATI_REG_CMD_AC_RESET, ATI_REG_CMD_AC_RESET);
		if (!--timeout) {
			dev_err(chip->card->dev, "codec reset timeout\n");
			break;
		}
	}

	/* deassert RESET and assert SYNC to make sure */
	atiixp_update(chip, CMD, ATI_REG_CMD_AC_SYNC|ATI_REG_CMD_AC_RESET,
		      ATI_REG_CMD_AC_SYNC|ATI_REG_CMD_AC_RESET);

	return 0;
}