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

__attribute__((used)) static inline void
cpuid(unsigned int op, unsigned int *a, unsigned int *b, unsigned int *c,
      unsigned int *d)
{
	__asm__ __volatile__ (".byte 0x53\n\tcpuid\n\t"
			      "movl %%ebx, %%esi\n\t.byte 0x5b"
			: "=a" (*a),
			"=S" (*b),
			"=c" (*c),
			"=d" (*d)
			: "a" (op));
}