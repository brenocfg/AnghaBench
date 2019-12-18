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
struct user_struct {int /*<<< orphan*/  locked_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_sub (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_unaccount_mem(struct user_struct *user, unsigned long nr_pages)
{
	atomic_long_sub(nr_pages, &user->locked_vm);
}