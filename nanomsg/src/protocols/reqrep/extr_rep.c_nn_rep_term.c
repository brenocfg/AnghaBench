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
struct nn_rep {int flags; int /*<<< orphan*/  xrep; int /*<<< orphan*/  backtrace; } ;

/* Variables and functions */
 int NN_REP_INPROGRESS ; 
 int /*<<< orphan*/  nn_chunkref_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_xrep_term (int /*<<< orphan*/ *) ; 

void nn_rep_term (struct nn_rep *self)
{
    if (self->flags & NN_REP_INPROGRESS)
        nn_chunkref_term (&self->backtrace);
    nn_xrep_term (&self->xrep);
}