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
struct msg_chunk {int /*<<< orphan*/  item; int /*<<< orphan*/  chunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_chunkref_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_free (struct msg_chunk*) ; 
 int /*<<< orphan*/  nn_list_erase (struct nn_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_list_item_term (int /*<<< orphan*/ *) ; 

void nn_msg_chunk_term (struct msg_chunk *it, struct nn_list *msg_array)
{
    nn_chunkref_term (&it->chunk);
    nn_list_erase (msg_array, &it->item);
    nn_list_item_term (&it->item);
    nn_free (it);
}