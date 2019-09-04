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
typedef  size_t uint32_t ;
struct link_packet {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int
get_bits(struct link_packet *packet, int offset, int width)
{
	uint32_t *data = (uint32_t *) packet;
	uint32_t index, shift, mask;

	index = offset / 32 + 1;
	shift = 32 - (offset & 31) - width;
	mask = width == 32 ? ~0 : (1 << width) - 1;

	return (data[index] >> shift) & mask;
}