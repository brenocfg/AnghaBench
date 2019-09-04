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
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT1724_RESET ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_vt1724_chip_reset(struct snd_ice1712 *ice)
{
	outb(VT1724_RESET , ICEREG1724(ice, CONTROL));
	inb(ICEREG1724(ice, CONTROL)); /* pci posting flush */
	msleep(10);
	outb(0, ICEREG1724(ice, CONTROL));
	inb(ICEREG1724(ice, CONTROL)); /* pci posting flush */
	msleep(10);
}