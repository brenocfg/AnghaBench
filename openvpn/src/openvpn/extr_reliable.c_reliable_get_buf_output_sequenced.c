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
struct reliable_entry {int /*<<< orphan*/  packet_id; scalar_t__ active; } ;
struct reliable {int size; int /*<<< orphan*/  packet_id; struct reliable_entry* array; } ;
struct gc_arena {int dummy; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  packet_id_type ;

/* Variables and functions */
 int /*<<< orphan*/  D_REL_LOW ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 struct buffer* reliable_get_buf (struct reliable*) ; 
 scalar_t__ reliable_pid_in_range1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ reliable_pid_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reliable_print_ids (struct reliable*,struct gc_arena*) ; 

struct buffer *
reliable_get_buf_output_sequenced(struct reliable *rel)
{
    struct gc_arena gc = gc_new();
    int i;
    packet_id_type min_id = 0;
    bool min_id_defined = false;
    struct buffer *ret = NULL;

    /* find minimum active packet_id */
    for (i = 0; i < rel->size; ++i)
    {
        const struct reliable_entry *e = &rel->array[i];
        if (e->active)
        {
            if (!min_id_defined || reliable_pid_min(e->packet_id, min_id))
            {
                min_id_defined = true;
                min_id = e->packet_id;
            }
        }
    }

    if (!min_id_defined || reliable_pid_in_range1(rel->packet_id, min_id, rel->size))
    {
        ret = reliable_get_buf(rel);
    }
    else
    {
        dmsg(D_REL_LOW, "ACK output sequence broken: %s", reliable_print_ids(rel, &gc));
    }
    gc_free(&gc);
    return ret;
}