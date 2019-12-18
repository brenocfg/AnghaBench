#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
struct TYPE_2__ {int num_ints; int bits_per_int; } ;

/* Variables and functions */
 int EMPTY_CODEWORD ; 
 int UINT64CONST (int) ; 
 TYPE_1__* simple8b_modes ; 

__attribute__((used)) static int
simple8b_decode(uint64 codeword, uint64 *decoded, uint64 base)
{
	int			selector = (codeword >> 60);
	int			nints = simple8b_modes[selector].num_ints;
	int			bits = simple8b_modes[selector].bits_per_int;
	uint64		mask = (UINT64CONST(1) << bits) - 1;
	uint64		curr_value;

	if (codeword == EMPTY_CODEWORD)
		return 0;

	curr_value = base;
	for (int i = 0; i < nints; i++)
	{
		uint64		diff = codeword & mask;

		curr_value += 1 + diff;
		decoded[i] = curr_value;
		codeword >>= bits;
	}
	return nints;
}