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
 int /*<<< orphan*/  AC97_CMD ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void revo_i2s_mclk_changed(struct snd_ice1712 *ice)
{
	/* assert PRST# to converters; MT05 bit 7 */
	outb(inb(ICEMT1724(ice, AC97_CMD)) | 0x80, ICEMT1724(ice, AC97_CMD));
	mdelay(5);
	/* deassert PRST# */
	outb(inb(ICEMT1724(ice, AC97_CMD)) & ~0x80, ICEMT1724(ice, AC97_CMD));
}