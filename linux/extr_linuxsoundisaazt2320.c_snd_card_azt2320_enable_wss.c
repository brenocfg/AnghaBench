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

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int snd_card_azt2320_command (unsigned long,int) ; 

__attribute__((used)) static int snd_card_azt2320_enable_wss(unsigned long port)
{
	int error;

	if ((error = snd_card_azt2320_command(port, 0x09)))
		return error;
	if ((error = snd_card_azt2320_command(port, 0x00)))
		return error;

	mdelay(5);
	return 0;
}