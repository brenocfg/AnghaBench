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
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPDIF_CFG ; 
 int /*<<< orphan*/  SPDIF_CTRL ; 
 unsigned char VT1724_CFG_SPDIF_OUT_EN ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_spdif_bits(struct snd_ice1712 *ice, unsigned int val)
{
	unsigned char cbit, disabled;

	cbit = inb(ICEREG1724(ice, SPDIF_CFG));
	disabled = cbit & ~VT1724_CFG_SPDIF_OUT_EN;
	if (cbit != disabled)
		outb(disabled, ICEREG1724(ice, SPDIF_CFG));
	outw(val, ICEMT1724(ice, SPDIF_CTRL));
	if (cbit != disabled)
		outb(cbit, ICEREG1724(ice, SPDIF_CFG));
	outw(val, ICEMT1724(ice, SPDIF_CTRL));
}