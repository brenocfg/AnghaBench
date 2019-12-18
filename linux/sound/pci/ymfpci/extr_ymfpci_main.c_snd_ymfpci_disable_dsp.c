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
typedef  int u32 ;
struct snd_ymfpci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_CONFIG ; 
 int /*<<< orphan*/  YDSXGR_STATUS ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_ymfpci_disable_dsp(struct snd_ymfpci *chip)
{
	u32 val;
	int timeout = 1000;

	val = snd_ymfpci_readl(chip, YDSXGR_CONFIG);
	if (val)
		snd_ymfpci_writel(chip, YDSXGR_CONFIG, 0x00000000);
	while (timeout-- > 0) {
		val = snd_ymfpci_readl(chip, YDSXGR_STATUS);
		if ((val & 0x00000002) == 0)
			break;
	}
}