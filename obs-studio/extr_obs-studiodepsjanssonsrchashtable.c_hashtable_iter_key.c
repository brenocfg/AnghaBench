#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* key; } ;
typedef  TYPE_1__ pair_t ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 TYPE_1__* ordered_list_to_pair (int /*<<< orphan*/ *) ; 

void *hashtable_iter_key(void *iter)
{
    pair_t *pair = ordered_list_to_pair((list_t *)iter);
    return pair->key;
}