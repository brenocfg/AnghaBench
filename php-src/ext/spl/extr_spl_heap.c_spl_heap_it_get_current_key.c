#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ zend_object_iterator ;
struct TYPE_8__ {TYPE_1__* heap; } ;
typedef  TYPE_3__ spl_heap_object ;
struct TYPE_6__ {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_3__* Z_SPLHEAP_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_heap_it_get_current_key(zend_object_iterator *iter, zval *key) /* {{{ */
{
	spl_heap_object *object = Z_SPLHEAP_P(&iter->data);

	ZVAL_LONG(key, object->heap->count - 1);
}