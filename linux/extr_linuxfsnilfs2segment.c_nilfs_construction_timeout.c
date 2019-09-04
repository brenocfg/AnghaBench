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
struct timer_list {int dummy; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_timer_task; } ;

/* Variables and functions */
 struct nilfs_sc_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_timer ; 
 struct nilfs_sc_info* sci ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nilfs_construction_timeout(struct timer_list *t)
{
	struct nilfs_sc_info *sci = from_timer(sci, t, sc_timer);

	wake_up_process(sci->sc_timer_task);
}