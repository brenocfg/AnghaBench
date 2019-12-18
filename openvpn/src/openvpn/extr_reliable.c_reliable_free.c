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
struct reliable_entry {int /*<<< orphan*/  buf; } ;
struct reliable {int size; struct reliable_entry* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_buf (int /*<<< orphan*/ *) ; 

void
reliable_free(struct reliable *rel)
{
    int i;
    for (i = 0; i < rel->size; ++i)
    {
        struct reliable_entry *e = &rel->array[i];
        free_buf(&e->buf);
    }
}