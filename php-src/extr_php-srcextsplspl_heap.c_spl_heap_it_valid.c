#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ zend_object_iterator ;
struct TYPE_7__ {TYPE_1__* heap; } ;
struct TYPE_5__ {scalar_t__ count; } ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 TYPE_4__* Z_SPLHEAP_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_heap_it_valid(zend_object_iterator *iter) /* {{{ */
{
	return ((Z_SPLHEAP_P(&iter->data))->heap->count != 0 ? SUCCESS : FAILURE);
}