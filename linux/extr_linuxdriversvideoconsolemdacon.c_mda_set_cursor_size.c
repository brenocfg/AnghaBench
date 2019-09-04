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
 int MDA_CURSOR_OFF ; 
 int mda_cursor_size_from ; 
 int mda_cursor_size_to ; 
 int /*<<< orphan*/  write_mda_b (int,int) ; 

__attribute__((used)) static inline void mda_set_cursor_size(int from, int to)
{
	if (mda_cursor_size_from==from && mda_cursor_size_to==to)
		return;
	
	if (from > to) {
		write_mda_b(MDA_CURSOR_OFF, 0x0a);	/* disable cursor */
	} else {
		write_mda_b(from, 0x0a);	/* cursor start */
		write_mda_b(to,   0x0b);	/* cursor end */
	}

	mda_cursor_size_from = from;
	mda_cursor_size_to   = to;
}