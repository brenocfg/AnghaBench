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
struct nn_dist {scalar_t__ count; int /*<<< orphan*/  pipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_list_term (int /*<<< orphan*/ *) ; 

void nn_dist_term (struct nn_dist *self)
{
    nn_assert (self->count == 0);
    nn_list_term (&self->pipes);
}