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
typedef  size_t uint ;
struct gasket_num_name {char const* snn_name; size_t snn_num; } ;

/* Variables and functions */

const char *gasket_num_name_lookup(uint num,
				   const struct gasket_num_name *table)
{
	uint i = 0;

	while (table[i].snn_name) {
		if (num == table[i].snn_num)
			break;
		++i;
	}

	return table[i].snn_name;
}