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
struct cs43130_bitwidth_map {unsigned int bitwidth; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cs43130_bitwidth_map const*) ; 
 struct cs43130_bitwidth_map const* cs43130_bitwidth_table ; 

__attribute__((used)) static const struct cs43130_bitwidth_map *cs43130_get_bitwidth_table(
				unsigned int bitwidth)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(cs43130_bitwidth_table); i++) {
		if (cs43130_bitwidth_table[i].bitwidth == bitwidth)
			return &cs43130_bitwidth_table[i];
	}

	return NULL;
}