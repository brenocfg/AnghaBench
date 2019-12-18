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
struct nn_ins_item {int /*<<< orphan*/  item; } ;
struct TYPE_2__ {int /*<<< orphan*/  sync; int /*<<< orphan*/  bound; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_list_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ self ; 

void nn_ins_unbind (struct nn_ins_item *item)
{
    nn_mutex_lock (&self.sync);
    nn_list_erase (&self.bound, &item->item);
    nn_mutex_unlock (&self.sync);
}