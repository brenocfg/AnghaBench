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
typedef  int u8 ;
struct mtpav {int dummy; } ;

/* Variables and functions */
 int SIGS_RFD ; 
 int /*<<< orphan*/  SREG ; 
 int snd_mtpav_getreg (struct mtpav*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_mtpav_wait_rfdhi(struct mtpav *chip)
{
	int counts = 10000;
	u8 sbyte;

	sbyte = snd_mtpav_getreg(chip, SREG);
	while (!(sbyte & SIGS_RFD) && counts--) {
		sbyte = snd_mtpav_getreg(chip, SREG);
		udelay(10);
	}
}