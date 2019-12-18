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
struct buffer {int dummy; } ;
struct reliable_entry {scalar_t__ packet_id; struct buffer buf; scalar_t__ active; } ;
struct reliable {int size; scalar_t__ packet_id; struct reliable_entry* array; } ;

/* Variables and functions */

struct buffer *
reliable_get_buf_sequenced(struct reliable *rel)
{
    int i;
    for (i = 0; i < rel->size; ++i)
    {
        struct reliable_entry *e = &rel->array[i];
        if (e->active && e->packet_id == rel->packet_id)
        {
            return &e->buf;
        }
    }
    return NULL;
}