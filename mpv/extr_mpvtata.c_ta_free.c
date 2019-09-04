#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ta_header {struct ta_header* ext; TYPE_2__* next; TYPE_1__* prev; int /*<<< orphan*/  (* destructor ) (void*) ;} ;
struct TYPE_4__ {TYPE_1__* prev; } ;
struct TYPE_3__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ta_header*) ; 
 struct ta_header* get_header (void*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  ta_dbg_remove (struct ta_header*) ; 
 int /*<<< orphan*/  ta_free_children (void*) ; 

void ta_free(void *ptr)
{
    struct ta_header *h = get_header(ptr);
    if (!h)
        return;
    if (h->ext && h->ext->destructor)
        h->ext->destructor(ptr);
    ta_free_children(ptr);
    if (h->next) {
        // Unlink from sibling list
        h->next->prev = h->prev;
        h->prev->next = h->next;
    }
    ta_dbg_remove(h);
    free(h->ext);
    free(h);
}