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

__attribute__((used)) static inline unsigned int to_tcon_channel(unsigned int channel)
{
	/* TCON register has a gap of 4 bits (1 channel) after channel 0 */
	return (channel == 0) ? 0 : (channel + 1);
}