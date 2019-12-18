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
struct nn_chunkref_chunk {int tag; void* chunk; } ;
struct nn_chunkref {int dummy; } ;

/* Variables and functions */

void nn_chunkref_init_chunk (struct nn_chunkref *self, void *chunk)
{
    struct nn_chunkref_chunk *ch;

    ch = (struct nn_chunkref_chunk*) self;
    ch->tag = 0xff;
    ch->chunk = chunk;
}