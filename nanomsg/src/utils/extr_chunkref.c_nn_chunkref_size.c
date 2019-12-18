#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nn_chunkref_chunk {int /*<<< orphan*/  chunk; } ;
struct TYPE_2__ {int* ref; } ;
struct nn_chunkref {TYPE_1__ u; } ;

/* Variables and functions */
 size_t nn_chunk_size (int /*<<< orphan*/ ) ; 

size_t nn_chunkref_size (struct nn_chunkref *self)
{
    return self->u.ref [0] == 0xff ?
        nn_chunk_size (((struct nn_chunkref_chunk*) self)->chunk) :
        self->u.ref [0];
}