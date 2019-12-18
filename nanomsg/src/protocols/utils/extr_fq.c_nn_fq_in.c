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
struct nn_fq_data {int /*<<< orphan*/  priodata; } ;
struct nn_fq {int /*<<< orphan*/  priolist; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_priolist_activate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nn_fq_in (struct nn_fq *self, struct nn_fq_data *data)
{
    nn_priolist_activate (&self->priolist, &data->priodata);
}