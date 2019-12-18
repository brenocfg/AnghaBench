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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 unsigned int CPLD_CKS_MASK ; 
 unsigned int CPLD_SYNC_SEL ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RATE ; 
 unsigned char VT1724_SPDIF_MASTER ; 
 unsigned int get_cks_val (unsigned int) ; 
 unsigned int get_cpld (struct snd_ice1712*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpld (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static void qtet_set_rate(struct snd_ice1712 *ice, unsigned int rate)
{
	unsigned int new;
	unsigned char val;
	/* switching ice1724 to external clock - supplied by ext. circuits */
	val = inb(ICEMT1724(ice, RATE));
	outb(val | VT1724_SPDIF_MASTER, ICEMT1724(ice, RATE));

	new =  (get_cpld(ice) & ~CPLD_CKS_MASK) | get_cks_val(rate);
	/* switch to internal clock, drop CPLD_SYNC_SEL */
	new &= ~CPLD_SYNC_SEL;
	/* dev_dbg(ice->card->dev, "QT - set_rate: old %x, new %x\n",
	   get_cpld(ice), new); */
	set_cpld(ice, new);
}