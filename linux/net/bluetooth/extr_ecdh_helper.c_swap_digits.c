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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  __swab64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void swap_digits(u64 *in, u64 *out, unsigned int ndigits)
{
	int i;

	for (i = 0; i < ndigits; i++)
		out[i] = __swab64(in[ndigits - 1 - i]);
}