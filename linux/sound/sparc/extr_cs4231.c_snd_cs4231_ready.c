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
struct snd_cs4231 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231U (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 int CS4231_INIT ; 
 int /*<<< orphan*/  REGSEL ; 
 int __cs4231_readb (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_cs4231_ready(struct snd_cs4231 *chip)
{
	int timeout;

	for (timeout = 250; timeout > 0; timeout--) {
		int val = __cs4231_readb(chip, CS4231U(chip, REGSEL));
		if ((val & CS4231_INIT) == 0)
			break;
		udelay(100);
	}
}