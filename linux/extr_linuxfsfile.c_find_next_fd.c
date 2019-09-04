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
struct fdtable {unsigned int max_fds; int /*<<< orphan*/  open_fds; int /*<<< orphan*/  full_fds_bits; } ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 unsigned int find_next_zero_bit (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int find_next_fd(struct fdtable *fdt, unsigned int start)
{
	unsigned int maxfd = fdt->max_fds;
	unsigned int maxbit = maxfd / BITS_PER_LONG;
	unsigned int bitbit = start / BITS_PER_LONG;

	bitbit = find_next_zero_bit(fdt->full_fds_bits, maxbit, bitbit) * BITS_PER_LONG;
	if (bitbit > maxfd)
		return maxfd;
	if (bitbit > start)
		start = bitbit;
	return find_next_zero_bit(fdt->open_fds, maxfd, start);
}