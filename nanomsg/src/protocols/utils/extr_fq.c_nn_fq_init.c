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
 int /*<<< orphan*/  nn_priolist_init (int /*<<< orphan*/ *) ; 

void nn_fq_init (struct nn_fq *self)
{
    nn_priolist_init (&self->priolist);
}