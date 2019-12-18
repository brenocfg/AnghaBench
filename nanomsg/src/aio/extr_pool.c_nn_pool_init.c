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
struct nn_pool {int /*<<< orphan*/  worker; } ;

/* Variables and functions */
 int nn_worker_init (int /*<<< orphan*/ *) ; 

int nn_pool_init (struct nn_pool *self)
{
    return nn_worker_init (&self->worker);
}