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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;

/* Variables and functions */
 int /*<<< orphan*/  zend_weakref_unsupported (char*) ; 

__attribute__((used)) static int zend_weakref_no_isset(zend_object *object, zend_string *member, int hse, void **rtc) {
	if (hse != 2) {
		zend_weakref_unsupported("properties");
	}
	return 0;
}