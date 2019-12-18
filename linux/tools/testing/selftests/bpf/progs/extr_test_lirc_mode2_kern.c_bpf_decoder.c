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
 scalar_t__ LIRC_IS_PULSE (unsigned int) ; 
 unsigned int LIRC_VALUE (unsigned int) ; 
 int /*<<< orphan*/  bpf_rc_keydown (unsigned int*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_rc_pointer_rel (unsigned int*,unsigned int,unsigned int) ; 

int bpf_decoder(unsigned int *sample)
{
	if (LIRC_IS_PULSE(*sample)) {
		unsigned int duration = LIRC_VALUE(*sample);

		if (duration & 0x10000)
			bpf_rc_keydown(sample, 0x40, duration & 0xffff, 0);
		if (duration & 0x20000)
			bpf_rc_pointer_rel(sample, (duration >> 8) & 0xff,
					   duration & 0xff);
	}

	return 0;
}