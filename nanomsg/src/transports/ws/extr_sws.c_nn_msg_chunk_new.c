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
struct nn_list {int dummy; } ;
struct msg_chunk {int /*<<< orphan*/  chunk; int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_assert (struct msg_chunk*) ; 
 struct msg_chunk* nn_alloc (int,char*) ; 
 void* nn_chunkref_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_chunkref_init (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  nn_list_end (struct nn_list*) ; 
 int /*<<< orphan*/  nn_list_insert (struct nn_list*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_list_item_init (int /*<<< orphan*/ *) ; 

void *nn_msg_chunk_new (size_t size, struct nn_list *msg_array)
{
    struct msg_chunk *self;

    self = nn_alloc (sizeof (struct msg_chunk), "msg_chunk");
    alloc_assert (self);

    nn_chunkref_init (&self->chunk, size);
    nn_list_item_init (&self->item);

    nn_list_insert (msg_array, &self->item, nn_list_end (msg_array));

    return nn_chunkref_data (&self->chunk);
}