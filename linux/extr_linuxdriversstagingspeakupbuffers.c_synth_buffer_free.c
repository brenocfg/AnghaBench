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
 scalar_t__ SYNTH_BUF_SIZE ; 
 scalar_t__ buff_in ; 
 scalar_t__ buff_out ; 

__attribute__((used)) static int synth_buffer_free(void)
{
	int chars_free;

	if (buff_in >= buff_out)
		chars_free = SYNTH_BUF_SIZE - (buff_in - buff_out);
	else
		chars_free = buff_out - buff_in;
	return chars_free;
}