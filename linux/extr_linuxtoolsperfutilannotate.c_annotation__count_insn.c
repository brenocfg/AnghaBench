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
typedef  size_t u64 ;
struct annotation {scalar_t__* offsets; } ;

/* Variables and functions */

__attribute__((used)) static unsigned annotation__count_insn(struct annotation *notes, u64 start, u64 end)
{
	unsigned n_insn = 0;
	u64 offset;

	for (offset = start; offset <= end; offset++) {
		if (notes->offsets[offset])
			n_insn++;
	}
	return n_insn;
}