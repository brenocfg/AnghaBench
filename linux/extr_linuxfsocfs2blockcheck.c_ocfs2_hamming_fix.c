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
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int calc_code_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int hweight32 (unsigned int) ; 
 int /*<<< orphan*/  ocfs2_clear_bit (unsigned int,void*) ; 
 int /*<<< orphan*/  ocfs2_set_bit (unsigned int,void*) ; 
 scalar_t__ ocfs2_test_bit (unsigned int,void*) ; 

void ocfs2_hamming_fix(void *data, unsigned int d, unsigned int nr,
		       unsigned int fix)
{
	unsigned int i, b;

	BUG_ON(!d);

	/*
	 * If the bit to fix has an hweight of 1, it's a parity bit.  One
	 * busted parity bit is its own error.  Nothing to do here.
	 */
	if (hweight32(fix) == 1)
		return;

	/*
	 * nr + d is the bit right past the data hunk we're looking at.
	 * If fix after that, nothing to do
	 */
	if (fix >= calc_code_bit(nr + d, NULL))
		return;

	/*
	 * nr is the offset in the data hunk we're starting at.  Let's
	 * start b at the offset in the code buffer.  See hamming_encode()
	 * for a more detailed description of 'b'.
	 */
	b = calc_code_bit(nr, NULL);
	/* If the fix is before this hunk, nothing to do */
	if (fix < b)
		return;

	for (i = 0; i < d; i++, b++)
	{
		/* Skip past parity bits */
		while (hweight32(b) == 1)
			b++;

		/*
		 * i is the offset in this data hunk.
		 * nr + i is the offset in the total data buffer.
		 * b is the offset in the total code buffer.
		 *
		 * Thus, when b == fix, bit i in the current hunk needs
		 * fixing.
		 */
		if (b == fix)
		{
			if (ocfs2_test_bit(i, data))
				ocfs2_clear_bit(i, data);
			else
				ocfs2_set_bit(i, data);
			break;
		}
	}
}