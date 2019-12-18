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
struct snd_ad1816a {int dummy; } ;

/* Variables and functions */
 unsigned short snd_ad1816a_read (struct snd_ad1816a*,unsigned char) ; 
 int /*<<< orphan*/  snd_ad1816a_write (struct snd_ad1816a*,unsigned char,unsigned short) ; 

__attribute__((used)) static void snd_ad1816a_write_mask(struct snd_ad1816a *chip, unsigned char reg,
				   unsigned short mask, unsigned short value)
{
	snd_ad1816a_write(chip, reg,
		(value & mask) | (snd_ad1816a_read(chip, reg) & ~mask));
}