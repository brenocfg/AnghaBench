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
struct snd_ymfpci {int /*<<< orphan*/  spdif_opened; int /*<<< orphan*/  rear_opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_MODE ; 
 int /*<<< orphan*/  YDSXGR_SECCONFIG ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int snd_ymfpci_readw (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ymfpci_writew (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ymfpci_close_extension(struct snd_ymfpci *chip)
{
	if (! chip->rear_opened) {
		if (! chip->spdif_opened)
			snd_ymfpci_writel(chip, YDSXGR_MODE,
					  snd_ymfpci_readl(chip, YDSXGR_MODE) & ~(1 << 30));
		snd_ymfpci_writew(chip, YDSXGR_SECCONFIG,
				  (snd_ymfpci_readw(chip, YDSXGR_SECCONFIG) & ~0x0330) & ~0x0010);
	}
}