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
struct nn_pipe {int dummy; } ;
struct nn_fq_data {int /*<<< orphan*/  priodata; } ;
struct nn_fq {int /*<<< orphan*/  priolist; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_priolist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nn_pipe*,int) ; 

void nn_fq_add (struct nn_fq *self, struct nn_fq_data *data,
    struct nn_pipe *pipe, int priority)
{
    nn_priolist_add (&self->priolist, &data->priodata, pipe, priority);
}