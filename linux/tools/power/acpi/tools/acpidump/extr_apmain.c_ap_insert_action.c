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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {char* argument; int /*<<< orphan*/  to_be_done; } ;

/* Variables and functions */
 size_t AP_MAX_ACTIONS ; 
 TYPE_1__* action_table ; 
 size_t current_action ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int ap_insert_action(char *argument, u32 to_be_done)
{

	/* Insert action and check for table overflow */

	action_table[current_action].argument = argument;
	action_table[current_action].to_be_done = to_be_done;

	current_action++;
	if (current_action > AP_MAX_ACTIONS) {
		fprintf(stderr, "Too many table options (max %d)\n",
			AP_MAX_ACTIONS);
		return (-1);
	}

	return (0);
}