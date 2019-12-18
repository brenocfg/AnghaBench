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
struct snd_gus_card {scalar_t__ uart_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_gf1_uart_cmd (struct snd_gus_card*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_gf1_uart_reset(struct snd_gus_card * gus, int close)
{
	snd_gf1_uart_cmd(gus, 0x03);	/* reset */
	if (!close && gus->uart_enable) {
		udelay(160);
		snd_gf1_uart_cmd(gus, 0x00);	/* normal operations */
	}
}