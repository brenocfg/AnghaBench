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
struct atiixp_modem {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ATI_REG_PHYS_OUT_ADDR_EN ; 
 int EBUSY ; 
 int /*<<< orphan*/  PHYS_OUT_ADDR ; 
 int atiixp_read (struct atiixp_modem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_atiixp_acquire_codec(struct atiixp_modem *chip)
{
	int timeout = 1000;

	while (atiixp_read(chip, PHYS_OUT_ADDR) & ATI_REG_PHYS_OUT_ADDR_EN) {
		if (! timeout--) {
			dev_warn(chip->card->dev, "codec acquire timeout\n");
			return -EBUSY;
		}
		udelay(1);
	}
	return 0;
}