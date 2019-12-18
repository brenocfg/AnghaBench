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
struct snd_m3 {int reset_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_PORT_CONTROL_REG_B ; 
 int REGB_ENABLE_RESET ; 
 int /*<<< orphan*/  snd_m3_outb (struct snd_m3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_m3_assp_continue(struct snd_m3 *chip)
{
	snd_m3_outb(chip, chip->reset_state | REGB_ENABLE_RESET, DSP_PORT_CONTROL_REG_B);
}