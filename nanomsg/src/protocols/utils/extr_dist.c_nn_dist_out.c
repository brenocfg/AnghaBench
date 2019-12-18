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
struct nn_dist_data {int /*<<< orphan*/  item; } ;
struct nn_dist {int /*<<< orphan*/  pipes; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nn_dist_out (struct nn_dist *self, struct nn_dist_data *data)
{
    ++self->count;
    nn_list_insert (&self->pipes, &data->item, nn_list_end (&self->pipes));
}