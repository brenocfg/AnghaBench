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
struct random_ready_callback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_ptr_key_work ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 

__attribute__((used)) static void fill_random_ptr_key(struct random_ready_callback *unused)
{
	/* This may be in an interrupt handler. */
	queue_work(system_unbound_wq, &enable_ptr_key_work);
}