#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double* x; } ;

/* Variables and functions */
 int ACADO_N ; 
 int ACADO_NX ; 
 TYPE_1__ acadoVariables ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void acado_printDifferentialVariables( )
{
	int i, j;
	printf("\nDifferential variables:\n[\n");
	for (i = 0; i < ACADO_N + 1; ++i)
	{
		for (j = 0; j < ACADO_NX; ++j)
			printf("\t%e", acadoVariables.x[i * ACADO_NX + j]);
		printf("\n");
	}
	printf("]\n\n");
}