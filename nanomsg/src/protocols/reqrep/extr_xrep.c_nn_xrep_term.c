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
struct nn_xrep {int /*<<< orphan*/  sockbase; int /*<<< orphan*/  outpipes; int /*<<< orphan*/  inpipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_fq_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_hash_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sockbase_term (int /*<<< orphan*/ *) ; 

void nn_xrep_term (struct nn_xrep *self)
{
    nn_fq_term (&self->inpipes);
    nn_hash_term (&self->outpipes);
    nn_sockbase_term (&self->sockbase);
}