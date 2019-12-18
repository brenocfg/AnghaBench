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
struct cpu_stat_data {int* cstate; int* pstate; } ;

/* Variables and functions */
 int MAX_CPU ; 
 int MAX_CSTATE_ENTRIES ; 
 int MAX_PSTATE_ENTRIES ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct cpu_stat_data* stat_data ; 

__attribute__((used)) static void cpu_stat_print(void)
{
	int i, j;
	char state_str[sizeof("cstate-9")];
	struct cpu_stat_data *data;

	/* Clear screen */
	printf("\033[2J");

	/* Header */
	printf("\nCPU states statistics:\n");
	printf("%-10s ", "state(ms)");

	for (i = 0; i < MAX_CSTATE_ENTRIES; i++) {
		sprintf(state_str, "cstate-%d", i);
		printf("%-11s ", state_str);
	}

	for (i = 0; i < MAX_PSTATE_ENTRIES; i++) {
		sprintf(state_str, "pstate-%d", i);
		printf("%-11s ", state_str);
	}

	printf("\n");

	for (j = 0; j < MAX_CPU; j++) {
		data = &stat_data[j];

		printf("CPU-%-6d ", j);
		for (i = 0; i < MAX_CSTATE_ENTRIES; i++)
			printf("%-11ld ", data->cstate[i] / 1000000);

		for (i = 0; i < MAX_PSTATE_ENTRIES; i++)
			printf("%-11ld ", data->pstate[i] / 1000000);

		printf("\n");
	}
}