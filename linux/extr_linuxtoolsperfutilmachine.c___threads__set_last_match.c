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
struct threads {struct thread* last_match; } ;
struct thread {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
__threads__set_last_match(struct threads *threads, struct thread *th)
{
	threads->last_match = th;
}