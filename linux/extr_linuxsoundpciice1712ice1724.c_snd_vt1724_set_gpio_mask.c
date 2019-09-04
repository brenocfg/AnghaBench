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
struct snd_ice1712 {int /*<<< orphan*/  vt1720; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_WRITE_MASK ; 
 int /*<<< orphan*/  GPIO_WRITE_MASK_22 ; 
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_vt1724_set_gpio_mask(struct snd_ice1712 *ice, unsigned int data)
{
	outw(data, ICEREG1724(ice, GPIO_WRITE_MASK));
	if (!ice->vt1720) /* VT1720 supports only 16 GPIO bits */
		outb((data >> 16) & 0xff, ICEREG1724(ice, GPIO_WRITE_MASK_22));
	inw(ICEREG1724(ice, GPIO_WRITE_MASK)); /* dummy read for pci-posting */
}