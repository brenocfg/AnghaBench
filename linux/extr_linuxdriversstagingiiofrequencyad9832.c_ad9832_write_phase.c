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
struct ad9832_state {int /*<<< orphan*/  phase_msg; int /*<<< orphan*/  spi; void** phase_data; } ;

/* Variables and functions */
 unsigned long AD9832_CMD_PHA16BITSW ; 
 unsigned long AD9832_CMD_PHA8BITSW ; 
 int /*<<< orphan*/  AD9832_PHASE_BITS ; 
 unsigned long ADD_SHIFT ; 
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 unsigned long CMD_SHIFT ; 
 int EINVAL ; 
 void* cpu_to_be16 (unsigned long) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad9832_write_phase(struct ad9832_state *st,
			      unsigned long addr, unsigned long phase)
{
	if (phase > BIT(AD9832_PHASE_BITS))
		return -EINVAL;

	st->phase_data[0] = cpu_to_be16((AD9832_CMD_PHA8BITSW << CMD_SHIFT) |
					(addr << ADD_SHIFT) |
					((phase >> 8) & 0xFF));
	st->phase_data[1] = cpu_to_be16((AD9832_CMD_PHA16BITSW << CMD_SHIFT) |
					((addr - 1) << ADD_SHIFT) |
					(phase & 0xFF));

	return spi_sync(st->spi, &st->phase_msg);
}