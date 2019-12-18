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
struct TYPE_2__ {int inited; int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_condvar_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ self ; 

__attribute__((used)) static void nn_lib_init(void)
{
    /*  This function is executed once to initialize global locks. */
    nn_mutex_init (&self.lock);
    nn_condvar_init (&self.cond);
    self.inited = 1;
}