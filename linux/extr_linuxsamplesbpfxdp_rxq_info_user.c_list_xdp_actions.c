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
 int XDP_ACTION_MAX ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** xdp_action_names ; 

__attribute__((used)) static void list_xdp_actions(void)
{
	int i;

	printf("Available XDP --action <options>\n");
	for (i = 0; i < XDP_ACTION_MAX; i++)
		printf("\t%s\n", xdp_action_names[i]);
	printf("\n");
}