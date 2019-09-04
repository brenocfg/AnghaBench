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
 int iucv_max_pathid ; 
 scalar_t__* iucv_path_table ; 

__attribute__((used)) static int iucv_path_table_empty(void)
{
	int i;

	for (i = 0; i < iucv_max_pathid; i++) {
		if (iucv_path_table[i])
			return 0;
	}
	return 1;
}