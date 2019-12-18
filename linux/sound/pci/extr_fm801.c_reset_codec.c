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
 int /*<<< orphan*/  AC97_RESET ; 
 int /*<<< orphan*/  CODEC_CTRL ; 
 int /*<<< orphan*/  fm801_readw (struct fm801*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm801_writew (struct fm801*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wait_for_codec (struct fm801*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset_codec(struct fm801 *chip)
{
	/* codec cold reset + AC'97 warm reset */
	fm801_writew(chip, CODEC_CTRL, (1 << 5) | (1 << 6));
	fm801_readw(chip, CODEC_CTRL); /* flush posting data */
	udelay(100);
	fm801_writew(chip, CODEC_CTRL, 0);

	return wait_for_codec(chip, 0, AC97_RESET, msecs_to_jiffies(750));
}