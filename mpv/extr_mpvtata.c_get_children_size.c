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
struct ta_header {size_t size; struct ta_header* next; TYPE_1__* ext; } ;
struct TYPE_2__ {struct ta_header children; } ;

/* Variables and functions */

__attribute__((used)) static size_t get_children_size(struct ta_header *h)
{
    size_t size = 0;
    if (h->ext) {
        struct ta_header *s;
        for (s = h->ext->children.next; s != &h->ext->children; s = s->next)
            size += s->size + get_children_size(s);
    }
    return size;
}