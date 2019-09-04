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
struct snd_ad1816a {int /*<<< orphan*/  lock; int /*<<< orphan*/  hardware; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD1816A_HW_AD1815 ; 
 int /*<<< orphan*/  AD1816A_HW_AD1816A ; 
 int /*<<< orphan*/  AD1816A_HW_AD18MAX10 ; 
 int /*<<< orphan*/  AD1816A_HW_AUTO ; 
 int /*<<< orphan*/  AD1816A_VERSION_ID ; 
 int /*<<< orphan*/  snd_ad1816a_read (struct snd_ad1816a*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_ad1816a_probe(struct snd_ad1816a *chip)
{
	unsigned long flags;

	spin_lock_irqsave(&chip->lock, flags);

	switch (chip->version = snd_ad1816a_read(chip, AD1816A_VERSION_ID)) {
	case 0:
		chip->hardware = AD1816A_HW_AD1815;
		break;
	case 1:
		chip->hardware = AD1816A_HW_AD18MAX10;
		break;
	case 3:
		chip->hardware = AD1816A_HW_AD1816A;
		break;
	default:
		chip->hardware = AD1816A_HW_AUTO;
	}

	spin_unlock_irqrestore(&chip->lock, flags);
	return 0;
}