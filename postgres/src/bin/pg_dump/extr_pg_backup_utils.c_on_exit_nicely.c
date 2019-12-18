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
typedef  int /*<<< orphan*/  on_exit_nicely_callback ;
struct TYPE_2__ {void* arg; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 size_t MAX_ON_EXIT_NICELY ; 
 int /*<<< orphan*/  exit_nicely (int) ; 
 size_t on_exit_nicely_index ; 
 TYPE_1__* on_exit_nicely_list ; 
 int /*<<< orphan*/  pg_log_fatal (char*) ; 

void
on_exit_nicely(on_exit_nicely_callback function, void *arg)
{
	if (on_exit_nicely_index >= MAX_ON_EXIT_NICELY)
	{
		pg_log_fatal("out of on_exit_nicely slots");
		exit_nicely(1);
	}
	on_exit_nicely_list[on_exit_nicely_index].function = function;
	on_exit_nicely_list[on_exit_nicely_index].arg = arg;
	on_exit_nicely_index++;
}