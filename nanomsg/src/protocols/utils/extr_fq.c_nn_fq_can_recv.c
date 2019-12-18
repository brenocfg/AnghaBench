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
struct nn_fq {int /*<<< orphan*/  priolist; } ;

/* Variables and functions */
 int nn_priolist_is_active (int /*<<< orphan*/ *) ; 

int nn_fq_can_recv (struct nn_fq *self)
{
    return nn_priolist_is_active (&self->priolist);
}