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
 int /*<<< orphan*/  __cons_write_ll (char const*,unsigned int const) ; 

__attribute__((used)) static inline void __cons_write(const char *obuf, int olen) {
	const unsigned int bucket = 64 * 1024;
	unsigned int i;
	for (i = 0; (i + bucket) < olen; i += bucket) {
		__cons_write_ll (obuf + i, bucket);
	}
	if (i < olen) {
		__cons_write_ll (obuf + i, olen - i);
	}
}