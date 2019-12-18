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
struct nn_list_item {scalar_t__ prev; } ;

/* Variables and functions */
 scalar_t__ NN_LIST_NOTINLIST ; 

int nn_list_item_isinlist (struct nn_list_item *self)
{
    return self->prev == NN_LIST_NOTINLIST ? 0 : 1;
}