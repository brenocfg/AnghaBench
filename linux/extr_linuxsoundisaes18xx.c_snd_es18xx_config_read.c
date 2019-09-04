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
struct snd_es18xx {scalar_t__ ctrl_port; } ;

/* Variables and functions */
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static int snd_es18xx_config_read(struct snd_es18xx *chip, unsigned char reg)
{
	int data;

	outb(reg, chip->ctrl_port);
	data = inb(chip->ctrl_port + 1);
	return data;
}