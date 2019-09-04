#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int uart_cmd; } ;
struct snd_gus_card {TYPE_1__ gf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_gf1_uart_cmd (struct snd_gus_card*,int) ; 

__attribute__((used)) static void snd_gf1_default_interrupt_handler_midi_in(struct snd_gus_card * gus)
{
	snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd &= ~0x80);
}