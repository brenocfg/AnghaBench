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
struct TYPE_2__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* function ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ GetCurrentThreadId () ; 
 int /*<<< orphan*/  _endthreadex (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ mainThreadId ; 
 int on_exit_nicely_index ; 
 TYPE_1__* on_exit_nicely_list ; 
 scalar_t__ parallel_init_done ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

void
exit_nicely(int code)
{
	int			i;

	for (i = on_exit_nicely_index - 1; i >= 0; i--)
		on_exit_nicely_list[i].function(code,
										on_exit_nicely_list[i].arg);

#ifdef WIN32
	if (parallel_init_done && GetCurrentThreadId() != mainThreadId)
		_endthreadex(code);
#endif

	exit(code);
}