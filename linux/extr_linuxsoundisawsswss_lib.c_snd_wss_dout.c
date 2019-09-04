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
struct snd_wss {unsigned char mce_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231P (int /*<<< orphan*/ ) ; 
 int CS4231_INIT ; 
 int /*<<< orphan*/  REG ; 
 int /*<<< orphan*/  REGSEL ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wss_inb (struct snd_wss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wss_outb (struct snd_wss*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void snd_wss_dout(struct snd_wss *chip, unsigned char reg,
			 unsigned char value)
{
	int timeout;

	for (timeout = 250;
	     timeout > 0 && (wss_inb(chip, CS4231P(REGSEL)) & CS4231_INIT);
	     timeout--)
		udelay(10);
	wss_outb(chip, CS4231P(REGSEL), chip->mce_bit | reg);
	wss_outb(chip, CS4231P(REG), value);
	mb();
}