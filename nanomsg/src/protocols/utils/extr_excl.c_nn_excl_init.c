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
struct nn_excl {int /*<<< orphan*/ * outpipe; int /*<<< orphan*/ * inpipe; int /*<<< orphan*/ * pipe; } ;

/* Variables and functions */

void nn_excl_init (struct nn_excl *self)
{
    self->pipe = NULL;
    self->inpipe = NULL;
    self->outpipe = NULL;
}