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
struct nn_xpub {int /*<<< orphan*/  sockbase; int /*<<< orphan*/  outpipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_dist_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_sockbase_term (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nn_xpub_term (struct nn_xpub *self)
{
    nn_dist_term (&self->outpipes);
    nn_sockbase_term (&self->sockbase);
}