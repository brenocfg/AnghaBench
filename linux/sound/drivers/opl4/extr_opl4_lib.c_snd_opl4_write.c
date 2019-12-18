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
typedef  int /*<<< orphan*/  u8 ;
struct snd_opl4 {scalar_t__ pcm_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_opl4_wait (struct snd_opl4*) ; 

void snd_opl4_write(struct snd_opl4 *opl4, u8 reg, u8 value)
{
	snd_opl4_wait(opl4);
	outb(reg, opl4->pcm_port);

	snd_opl4_wait(opl4);
	outb(value, opl4->pcm_port + 1);
}