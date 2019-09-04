#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_sgio2audio {int /*<<< orphan*/  ad1843_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  codec_control; } ;
struct TYPE_5__ {TYPE_1__ audio; } ;
struct TYPE_6__ {TYPE_2__ perif; } ;

/* Variables and functions */
 int CODEC_CONTROL_ADDRESS_SHIFT ; 
 int CODEC_CONTROL_WORD_SHIFT ; 
 TYPE_3__* mace ; 
 int readq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_ad1843_reg(void *priv, int reg, int word)
{
	struct snd_sgio2audio *chip = priv;
	int val;
	unsigned long flags;

	spin_lock_irqsave(&chip->ad1843_lock, flags);

	writeq((reg << CODEC_CONTROL_ADDRESS_SHIFT) |
	       (word << CODEC_CONTROL_WORD_SHIFT),
	       &mace->perif.audio.codec_control);
	wmb();
	val = readq(&mace->perif.audio.codec_control); /* flush bus */
	udelay(200);

	spin_unlock_irqrestore(&chip->ad1843_lock, flags);
	return 0;
}