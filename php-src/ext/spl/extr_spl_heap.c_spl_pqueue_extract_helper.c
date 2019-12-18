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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/  priority; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ spl_pqueue_elem ;

/* Variables and functions */
 int SPL_PQUEUE_EXTR_BOTH ; 
 int SPL_PQUEUE_EXTR_DATA ; 
 int SPL_PQUEUE_EXTR_PRIORITY ; 
 int /*<<< orphan*/  ZEND_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TRY_ADDREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_zval_ex (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_pqueue_extract_helper(zval *result, spl_pqueue_elem *elem, int flags) /* {{{ */
{
	if ((flags & SPL_PQUEUE_EXTR_BOTH) == SPL_PQUEUE_EXTR_BOTH) {
		array_init(result);
		Z_TRY_ADDREF(elem->data);
		add_assoc_zval_ex(result, "data", sizeof("data") - 1, &elem->data);
		Z_TRY_ADDREF(elem->priority);
		add_assoc_zval_ex(result, "priority", sizeof("priority") - 1, &elem->priority);
		return;
	}

	if (flags & SPL_PQUEUE_EXTR_DATA) {
		ZVAL_COPY(result, &elem->data);
		return;
	}

	if (flags & SPL_PQUEUE_EXTR_PRIORITY) {
		ZVAL_COPY(result, &elem->priority);
		return;
	}

	ZEND_ASSERT(0);
}