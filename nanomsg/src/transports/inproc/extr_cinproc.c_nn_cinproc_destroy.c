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
struct nn_cinproc {int /*<<< orphan*/  item; int /*<<< orphan*/  fsm; int /*<<< orphan*/  sinprocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_free (struct nn_cinproc*) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_ins_item_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_cinproc_destroy (void *self)
{
    struct nn_cinproc *cinproc = self;

    nn_list_term (&cinproc->sinprocs);
    nn_fsm_term (&cinproc->fsm);
    nn_ins_item_term (&cinproc->item);

    nn_free (cinproc);
}