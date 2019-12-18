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
typedef  int /*<<< orphan*/  uint32_t ;
struct nn_atomic {int /*<<< orphan*/  sync; int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_mutex_init (int /*<<< orphan*/ *) ; 

void nn_atomic_init (struct nn_atomic *self, uint32_t n)
{
    self->n = n;
#if defined NN_ATOMIC_MUTEX
    nn_mutex_init (&self->sync);
#endif
}