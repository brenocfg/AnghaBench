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
struct thread {int dummy; } ;
struct hist_entry {struct thread const* thread; } ;

/* Variables and functions */
 int HIST_FILTER__THREAD ; 

__attribute__((used)) static int hist_entry__thread_filter(struct hist_entry *he, int type, const void *arg)
{
	const struct thread *th = arg;

	if (type != HIST_FILTER__THREAD)
		return -1;

	return th && he->thread != th;
}