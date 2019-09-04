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
typedef  int u16 ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int oxygen_read_ac97 (struct oxygen*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  oxygen_write_ac97 (struct oxygen*,unsigned int,unsigned int,int) ; 

void oxygen_write_ac97_masked(struct oxygen *chip, unsigned int codec,
			      unsigned int index, u16 data, u16 mask)
{
	u16 value = oxygen_read_ac97(chip, codec, index);
	value &= ~mask;
	value |= data & mask;
	oxygen_write_ac97(chip, codec, index, value);
}