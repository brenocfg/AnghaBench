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
struct snd_ymfpci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_CONFIG ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_ymfpci_enable_dsp(struct snd_ymfpci *chip)
{
	snd_ymfpci_writel(chip, YDSXGR_CONFIG, 0x00000001);
}