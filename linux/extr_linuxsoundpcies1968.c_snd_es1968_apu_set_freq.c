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
struct es1968 {int dummy; } ;

/* Variables and functions */
 int apu_get_register (struct es1968*,int,int) ; 
 int /*<<< orphan*/  apu_set_register (struct es1968*,int,int,int) ; 

__attribute__((used)) static void snd_es1968_apu_set_freq(struct es1968 *chip, int apu, int freq)
{
	apu_set_register(chip, apu, 2,
			   (apu_get_register(chip, apu, 2) & 0x00FF) |
			   ((freq & 0xff) << 8) | 0x10);
	apu_set_register(chip, apu, 3, freq >> 8);
}