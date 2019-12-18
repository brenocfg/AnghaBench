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
struct snd_emu10k1 {scalar_t__ audigy; } ;

/* Variables and functions */
 scalar_t__ A_MICROCODEBASE ; 
 scalar_t__ MICROCODEBASE ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void snd_emu10k1_efx_write(struct snd_emu10k1 *emu, unsigned int pc, unsigned int data)
{
	pc += emu->audigy ? A_MICROCODEBASE : MICROCODEBASE;
	snd_emu10k1_ptr_write(emu, pc, 0, data);
}