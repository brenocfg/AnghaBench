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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct nm256 {int mixer_status_mask; int /*<<< orphan*/  mixer_status_offset; } ;

/* Variables and functions */
 int snd_nm256_readw (struct nm256*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
snd_nm256_ac97_ready(struct nm256 *chip)
{
	int timeout = 10;
	u32 testaddr;
	u16 testb;

	testaddr = chip->mixer_status_offset;
	testb = chip->mixer_status_mask;

	/* 
	 * Loop around waiting for the mixer to become ready. 
	 */
	while (timeout-- > 0) {
		if ((snd_nm256_readw(chip, testaddr) & testb) == 0)
			return 1;
		udelay(100);
	}
	return 0;
}