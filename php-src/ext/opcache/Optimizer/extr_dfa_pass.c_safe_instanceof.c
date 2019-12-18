#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ce_flags; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  int zend_bool ;

/* Variables and functions */
 int ZEND_ACC_LINKED ; 
 int instanceof_function (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static zend_bool safe_instanceof(zend_class_entry *ce1, zend_class_entry *ce2) {
	if (ce1 == ce2) {
		return 1;
	}
	if (!(ce1->ce_flags & ZEND_ACC_LINKED)) {
		/* This case could be generalized, similarly to unlinked_instanceof */
		return 0;
	}
	return instanceof_function(ce1, ce2);
}