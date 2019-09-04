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
typedef  int u16 ;
struct snd_ymfpci {int dummy; } ;
struct snd_ac97 {struct snd_ymfpci* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  YDSXGR_AC97CMDDATA ; 
 int YDSXG_AC97WRITECMD ; 
 int /*<<< orphan*/  snd_ymfpci_codec_ready (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_ymfpci_codec_write(struct snd_ac97 *ac97, u16 reg, u16 val)
{
	struct snd_ymfpci *chip = ac97->private_data;
	u32 cmd;
	
	snd_ymfpci_codec_ready(chip, 0);
	cmd = ((YDSXG_AC97WRITECMD | reg) << 16) | val;
	snd_ymfpci_writel(chip, YDSXGR_AC97CMDDATA, cmd);
}