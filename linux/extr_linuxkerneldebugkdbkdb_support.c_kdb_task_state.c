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
struct task_struct {int dummy; } ;

/* Variables and functions */
 char kdb_task_state_char (struct task_struct const*) ; 
 unsigned long kdb_task_state_string (char*) ; 

unsigned long kdb_task_state(const struct task_struct *p, unsigned long mask)
{
	char state[] = { kdb_task_state_char(p), '\0' };
	return (mask & kdb_task_state_string(state)) != 0;
}