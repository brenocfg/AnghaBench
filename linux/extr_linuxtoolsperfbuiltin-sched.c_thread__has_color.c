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
union map_priv {int color; int /*<<< orphan*/  ptr; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  thread__priv (struct thread*) ; 

__attribute__((used)) static bool thread__has_color(struct thread *thread)
{
	union map_priv priv = {
		.ptr = thread__priv(thread),
	};

	return priv.color;
}