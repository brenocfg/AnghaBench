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
struct threads {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __threads__set_last_match (struct threads*,struct thread*) ; 
 scalar_t__ perf_singlethreaded ; 

__attribute__((used)) static void
threads__set_last_match(struct threads *threads, struct thread *th)
{
	if (perf_singlethreaded)
		__threads__set_last_match(threads, th);
}