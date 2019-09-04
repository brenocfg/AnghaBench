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
 int* buff_in ; 
 int* buff_out ; 
 int* buffer_end ; 
 int* synth_buffer ; 

void synth_buffer_skip_nonlatin1(void)
{
	while (buff_out != buff_in) {
		if (*buff_out < 0x100)
			return;
		buff_out++;
		if (buff_out > buffer_end)
			buff_out = synth_buffer;
	}
}