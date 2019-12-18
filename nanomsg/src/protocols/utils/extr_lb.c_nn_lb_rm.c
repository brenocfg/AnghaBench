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
struct nn_lb_data {int /*<<< orphan*/  priodata; } ;
struct nn_lb {int /*<<< orphan*/  priolist; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_priolist_rm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nn_lb_rm (struct nn_lb *self, struct nn_lb_data *data)
{
    nn_priolist_rm (&self->priolist, &data->priodata);
}