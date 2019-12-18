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
struct kasan_track {int /*<<< orphan*/  stack; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  save_stack (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_track(struct kasan_track *track, gfp_t flags)
{
	track->pid = current->pid;
	track->stack = save_stack(flags);
}