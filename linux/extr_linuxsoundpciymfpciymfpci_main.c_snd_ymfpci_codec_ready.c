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
typedef  int /*<<< orphan*/  u32 ;
struct snd_ymfpci {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  YDSXGR_PRISTATUSADR ; 
 int /*<<< orphan*/  YDSXGR_SECSTATUSADR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int snd_ymfpci_readw (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int snd_ymfpci_codec_ready(struct snd_ymfpci *chip, int secondary)
{
	unsigned long end_time;
	u32 reg = secondary ? YDSXGR_SECSTATUSADR : YDSXGR_PRISTATUSADR;
	
	end_time = jiffies + msecs_to_jiffies(750);
	do {
		if ((snd_ymfpci_readw(chip, reg) & 0x8000) == 0)
			return 0;
		schedule_timeout_uninterruptible(1);
	} while (time_before(jiffies, end_time));
	dev_err(chip->card->dev,
		"codec_ready: codec %i is not ready [0x%x]\n",
		secondary, snd_ymfpci_readw(chip, reg));
	return -EBUSY;
}