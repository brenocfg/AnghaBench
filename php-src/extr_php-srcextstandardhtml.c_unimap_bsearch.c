#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned short un_code_point; unsigned char cs_code; } ;
typedef  TYPE_1__ uni_to_enc ;

/* Variables and functions */

__attribute__((used)) static inline unsigned char unimap_bsearch(const uni_to_enc *table, unsigned code_key_a, size_t num)
{
	const uni_to_enc *l = table,
					 *h = &table[num-1],
					 *m;
	unsigned short code_key;

	/* we have no mappings outside the BMP */
	if (code_key_a > 0xFFFFU)
		return 0;

	code_key = (unsigned short) code_key_a;

	while (l <= h) {
		m = l + (h - l) / 2;
		if (code_key < m->un_code_point)
			h = m - 1;
		else if (code_key > m->un_code_point)
			l = m + 1;
		else
			return m->cs_code;
	}
	return 0;
}