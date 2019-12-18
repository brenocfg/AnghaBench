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
struct ta_header {struct ta_ext_header* ext; } ;
struct TYPE_2__ {struct TYPE_2__* prev; } ;
struct ta_ext_header {TYPE_1__ children; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTR_FROM_HEADER (TYPE_1__*) ; 
 struct ta_header* get_header (void*) ; 
 int /*<<< orphan*/  ta_free (int /*<<< orphan*/ ) ; 

void ta_free_children(void *ptr)
{
    struct ta_header *h = get_header(ptr);
    struct ta_ext_header *eh = h ? h->ext : NULL;
    if (!eh)
        return;
    while (eh->children.prev != &eh->children)
        ta_free(PTR_FROM_HEADER(eh->children.prev));
}