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
typedef  scalar_t__ time_t ;
struct reliable_entry {scalar_t__ const next_try; scalar_t__ active; } ;
struct reliable {int size; struct reliable_entry* array; } ;
struct gc_arena {int dummy; } ;
typedef  scalar_t__ interval_t ;

/* Variables and functions */
 scalar_t__ BIG_TIMEOUT ; 
 int /*<<< orphan*/  D_REL_DEBUG ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 scalar_t__ min_int (scalar_t__,scalar_t__ const) ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  reliable_print_ids (struct reliable const*,struct gc_arena*) ; 

interval_t
reliable_send_timeout(const struct reliable *rel)
{
    struct gc_arena gc = gc_new();
    interval_t ret = BIG_TIMEOUT;
    int i;
    const time_t local_now = now;

    for (i = 0; i < rel->size; ++i)
    {
        const struct reliable_entry *e = &rel->array[i];
        if (e->active)
        {
            if (e->next_try <= local_now)
            {
                ret = 0;
                break;
            }
            else
            {
                ret = min_int(ret, e->next_try - local_now);
            }
        }
    }

    dmsg(D_REL_DEBUG, "ACK reliable_send_timeout %d %s",
         (int) ret,
         reliable_print_ids(rel, &gc));

    gc_free(&gc);
    return ret;
}