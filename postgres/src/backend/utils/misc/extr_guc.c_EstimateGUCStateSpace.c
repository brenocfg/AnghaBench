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
typedef  int Size ;

/* Variables and functions */
 int add_size (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  estimate_variable_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * guc_variables ; 
 int num_guc_variables ; 

Size
EstimateGUCStateSpace(void)
{
	Size		size;
	int			i;

	/* Add space reqd for saving the data size of the guc state */
	size = sizeof(Size);

	/* Add up the space needed for each GUC variable */
	for (i = 0; i < num_guc_variables; i++)
		size = add_size(size,
						estimate_variable_size(guc_variables[i]));

	return size;
}