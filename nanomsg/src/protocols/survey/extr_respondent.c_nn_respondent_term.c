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
struct nn_respondent {int flags; int /*<<< orphan*/  xrespondent; int /*<<< orphan*/  backtrace; } ;

/* Variables and functions */
 int NN_RESPONDENT_INPROGRESS ; 
 int /*<<< orphan*/  nn_chunkref_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_xrespondent_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_respondent_term (struct nn_respondent *self)
{
    if (self->flags & NN_RESPONDENT_INPROGRESS)
        nn_chunkref_term (&self->backtrace);
    nn_xrespondent_term (&self->xrespondent);
}