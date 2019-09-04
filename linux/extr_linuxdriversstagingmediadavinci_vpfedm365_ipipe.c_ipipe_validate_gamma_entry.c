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
struct vpfe_ipipe_gamma_entry {scalar_t__ slope; scalar_t__ offset; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GAMMA_MASK ; 

__attribute__((used)) static int
ipipe_validate_gamma_entry(struct vpfe_ipipe_gamma_entry *table, int size)
{
	int i;

	if (!table)
		return -EINVAL;

	for (i = 0; i < size; i++)
		if (table[i].slope > GAMMA_MASK ||
		    table[i].offset > GAMMA_MASK)
			return -EINVAL;

	return 0;
}