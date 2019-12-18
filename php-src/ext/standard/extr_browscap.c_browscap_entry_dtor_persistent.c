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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {scalar_t__ parent; scalar_t__ pattern; } ;
typedef  TYPE_1__ browscap_entry ;

/* Variables and functions */
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pefree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zend_string_release_ex (scalar_t__,int) ; 

__attribute__((used)) static void browscap_entry_dtor_persistent(zval *zvalue)
{
	browscap_entry *entry = Z_PTR_P(zvalue);
	zend_string_release_ex(entry->pattern, 1);
	if (entry->parent) {
		zend_string_release_ex(entry->parent, 1);
	}
	pefree(entry, 1);
}