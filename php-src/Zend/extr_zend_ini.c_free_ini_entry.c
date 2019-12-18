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
struct TYPE_3__ {scalar_t__ orig_value; scalar_t__ value; scalar_t__ name; } ;
typedef  TYPE_1__ zend_ini_entry ;

/* Variables and functions */
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_string_release (scalar_t__) ; 
 int /*<<< orphan*/  zend_string_release_ex (scalar_t__,int) ; 

__attribute__((used)) static void free_ini_entry(zval *zv) /* {{{ */
{
	zend_ini_entry *entry = (zend_ini_entry*)Z_PTR_P(zv);

	zend_string_release_ex(entry->name, 1);
	if (entry->value) {
		zend_string_release(entry->value);
	}
	if (entry->orig_value) {
		zend_string_release_ex(entry->orig_value, 1);
	}
	free(entry);
}