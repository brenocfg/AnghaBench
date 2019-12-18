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
typedef  size_t uint32_t ;
struct nn_hash {size_t slots; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_term (int /*<<< orphan*/ *) ; 

void nn_hash_term (struct nn_hash *self)
{
    uint32_t i;

    for (i = 0; i != self->slots; ++i)
        nn_list_term (&self->array [i]);
    nn_free (self->array);
}