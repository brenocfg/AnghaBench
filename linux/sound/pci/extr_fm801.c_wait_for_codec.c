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
struct fm801 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CMD ; 
 int EIO ; 
 unsigned int FM801_AC97_ADDR_SHIFT ; 
 int FM801_AC97_BUSY ; 
 unsigned short FM801_AC97_READ ; 
 int FM801_AC97_VALID ; 
 int fm801_readw (struct fm801*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm801_writew (struct fm801*,int /*<<< orphan*/ ,unsigned short) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_for_codec(struct fm801 *chip, unsigned int codec_id,
			  unsigned short reg, unsigned long waits)
{
	unsigned long timeout = jiffies + waits;

	fm801_writew(chip, AC97_CMD,
		     reg | (codec_id << FM801_AC97_ADDR_SHIFT) | FM801_AC97_READ);
	udelay(5);
	do {
		if ((fm801_readw(chip, AC97_CMD) &
		     (FM801_AC97_VALID | FM801_AC97_BUSY)) == FM801_AC97_VALID)
			return 0;
		schedule_timeout_uninterruptible(1);
	} while (time_after(timeout, jiffies));
	return -EIO;
}