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
struct ebt_table_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int NF_BR_BROUTING ; 

__attribute__((used)) static int check(const struct ebt_table_info *info, unsigned int valid_hooks)
{
	if (valid_hooks & ~(1 << NF_BR_BROUTING))
		return -EINVAL;
	return 0;
}