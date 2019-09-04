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
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static inline int __bail(int for_realz, bool no_print, __u8 step)
{
	if (for_realz) {
		if (no_print)
			_exit(step);
		abort();
	}
	return 0;
}