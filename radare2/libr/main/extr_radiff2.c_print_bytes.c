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
typedef  int /*<<< orphan*/  ut8 ;

/* Variables and functions */
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ *,int) ; 

void print_bytes(const void *p, size_t len, bool big_endian) {
	size_t i;
	for (i = 0; i < len; ++i) {
		ut8 ch = ((ut8*) p)[big_endian ? (len - i - 1) : i];
		write (1, &ch, 1);
	}
}