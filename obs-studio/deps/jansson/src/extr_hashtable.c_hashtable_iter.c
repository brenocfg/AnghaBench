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
struct TYPE_4__ {int /*<<< orphan*/  ordered_list; } ;
typedef  TYPE_1__ hashtable_t ;

/* Variables and functions */
 void* hashtable_iter_next (TYPE_1__*,int /*<<< orphan*/ *) ; 

void *hashtable_iter(hashtable_t *hashtable)
{
    return hashtable_iter_next(hashtable, &hashtable->ordered_list);
}