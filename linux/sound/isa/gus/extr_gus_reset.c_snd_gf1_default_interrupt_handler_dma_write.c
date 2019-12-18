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
struct snd_gus_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_gf1_i_write8 (struct snd_gus_card*,int,int) ; 

__attribute__((used)) static void snd_gf1_default_interrupt_handler_dma_write(struct snd_gus_card * gus)
{
	snd_gf1_i_write8(gus, 0x41, 0x00);
}