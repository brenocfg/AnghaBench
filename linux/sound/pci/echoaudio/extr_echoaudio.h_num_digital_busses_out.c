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
struct echoaudio {int dummy; } ;

/* Variables and functions */
 int num_analog_busses_out (struct echoaudio const*) ; 
 int num_busses_out (struct echoaudio const*) ; 

__attribute__((used)) static inline int num_digital_busses_out(const struct echoaudio *chip)
{
	return num_busses_out(chip) - num_analog_busses_out(chip);
}