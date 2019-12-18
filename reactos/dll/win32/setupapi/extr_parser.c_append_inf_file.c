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
struct inf_file {struct inf_file* next; } ;

/* Variables and functions */
 struct inf_file* InterlockedCompareExchangePointer (void**,struct inf_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void append_inf_file( struct inf_file *parent, struct inf_file *child )
{
    struct inf_file **ppnext = &parent->next;
    child->next = NULL;

    for (;;)
    {
        struct inf_file *next = InterlockedCompareExchangePointer( (void **)ppnext, child, NULL );
        if (!next) return;
        ppnext = &next->next;
    }
}