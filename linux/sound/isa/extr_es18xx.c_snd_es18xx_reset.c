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
struct snd_es18xx {scalar_t__ port; } ;

/* Variables and functions */
 int MILLISECOND ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int snd_es18xx_reset(struct snd_es18xx *chip)
{
	int i;
        outb(0x03, chip->port + 0x06);
        inb(chip->port + 0x06);
        outb(0x00, chip->port + 0x06);
        for(i = 0; i < MILLISECOND && !(inb(chip->port + 0x0E) & 0x80); i++);
        if (inb(chip->port + 0x0A) != 0xAA)
                return -1;
	return 0;
}