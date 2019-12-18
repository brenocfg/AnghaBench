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
struct reliable_entry {int /*<<< orphan*/  timeout; int /*<<< orphan*/  next_try; scalar_t__ active; } ;
struct reliable {int hold; int size; int /*<<< orphan*/  initial_timeout; struct reliable_entry* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_REL_DEBUG ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  now ; 

void
reliable_schedule_now(struct reliable *rel)
{
    int i;
    dmsg(D_REL_DEBUG, "ACK reliable_schedule_now");
    rel->hold = false;
    for (i = 0; i < rel->size; ++i)
    {
        struct reliable_entry *e = &rel->array[i];
        if (e->active)
        {
            e->next_try = now;
            e->timeout = rel->initial_timeout;
        }
    }
}