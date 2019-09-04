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
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  spl_ce_SplPriorityQueue ; 
 int /*<<< orphan*/ * spl_heap_object_get_debug_info_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static HashTable* spl_pqueue_object_get_debug_info(zend_object *obj, int *is_temp) /* {{{ */
{
	return spl_heap_object_get_debug_info_helper(spl_ce_SplPriorityQueue, obj, is_temp);
}