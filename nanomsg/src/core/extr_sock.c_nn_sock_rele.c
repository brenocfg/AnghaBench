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
struct nn_sock {scalar_t__ holds; int /*<<< orphan*/  relesem; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_sem_post (int /*<<< orphan*/ *) ; 

void nn_sock_rele (struct nn_sock *self)
{
    self->holds--;
    if (self->holds == 0) {
        nn_sem_post (&self->relesem);
    }
}