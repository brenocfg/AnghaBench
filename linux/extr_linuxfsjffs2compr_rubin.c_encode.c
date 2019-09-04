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
struct rubin_state {int q; int p; int /*<<< orphan*/  pp; int /*<<< orphan*/  bit_number; } ;

/* Variables and functions */
 int LOWER_BITS_RUBIN ; 
 int UPPER_BIT_RUBIN ; 
 int pushbit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int encode(struct rubin_state *rs, long A, long B, int symbol)
{

	long i0, i1;
	int ret;

	while ((rs->q >= UPPER_BIT_RUBIN) ||
	       ((rs->p + rs->q) <= UPPER_BIT_RUBIN)) {
		rs->bit_number++;

		ret = pushbit(&rs->pp, (rs->q & UPPER_BIT_RUBIN) ? 1 : 0, 0);
		if (ret)
			return ret;
		rs->q &= LOWER_BITS_RUBIN;
		rs->q <<= 1;
		rs->p <<= 1;
	}
	i0 = A * rs->p / (A + B);
	if (i0 <= 0)
		i0 = 1;

	if (i0 >= rs->p)
		i0 = rs->p - 1;

	i1 = rs->p - i0;

	if (symbol == 0)
		rs->p = i0;
	else {
		rs->p = i1;
		rs->q += i0;
	}
	return 0;
}