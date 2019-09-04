#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* lv_used_next; struct TYPE_4__* lv_used_prev; } ;
typedef  TYPE_1__ list_T ;

/* Variables and functions */
 scalar_t__ alloc_clear (int) ; 
 TYPE_1__* first_list ; 

list_T *
list_alloc()
{
    list_T  *l;

    l = (list_T *)alloc_clear(sizeof(list_T));
    if (l != NULL)
    {
	/* Prepend the list to the list of lists for garbage collection. */
	if (first_list != NULL)
	    first_list->lv_used_prev = l;
	l->lv_used_prev = NULL;
	l->lv_used_next = first_list;
	first_list = l;
    }
    return l;
}