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
struct snd_wss {int /*<<< orphan*/  thinkpad_flag; } ;

/* Variables and functions */
 int AD1848_THINKPAD_CS4248_ENABLE_BIT ; 
 int /*<<< orphan*/  AD1848_THINKPAD_CTL_PORT1 ; 
 int /*<<< orphan*/  AD1848_THINKPAD_CTL_PORT2 ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_wss_thinkpad_twiddle(struct snd_wss *chip, int on)
{
	int tmp;

	if (!chip->thinkpad_flag)
		return;

	outb(0x1c, AD1848_THINKPAD_CTL_PORT1);
	tmp = inb(AD1848_THINKPAD_CTL_PORT2);

	if (on)
		/* turn it on */
		tmp |= AD1848_THINKPAD_CS4248_ENABLE_BIT;
	else
		/* turn it off */
		tmp &= ~AD1848_THINKPAD_CS4248_ENABLE_BIT;

	outb(tmp, AD1848_THINKPAD_CTL_PORT2);
}