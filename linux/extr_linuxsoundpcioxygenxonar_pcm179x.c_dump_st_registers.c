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
struct snd_info_buffer {int dummy; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_cs2000_registers (struct oxygen*,struct snd_info_buffer*) ; 
 int /*<<< orphan*/  dump_pcm1796_registers (struct oxygen*,struct snd_info_buffer*) ; 

__attribute__((used)) static void dump_st_registers(struct oxygen *chip,
			      struct snd_info_buffer *buffer)
{
	dump_pcm1796_registers(chip, buffer);
	dump_cs2000_registers(chip, buffer);
}