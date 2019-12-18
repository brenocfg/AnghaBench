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
typedef  int /*<<< orphan*/  zend_function ;
typedef  int /*<<< orphan*/  zend_class_entry ;
typedef  scalar_t__ inheritance_status ;

/* Variables and functions */
 scalar_t__ EXPECTED (int) ; 
 scalar_t__ INHERITANCE_ERROR ; 
 scalar_t__ INHERITANCE_SUCCESS ; 
 scalar_t__ INHERITANCE_UNRESOLVED ; 
 scalar_t__ UNEXPECTED (int) ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int /*<<< orphan*/  add_compatibility_obligation (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  emit_incompatible_method_error (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ zend_do_perform_implementation_check (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void perform_delayable_implementation_check(
		zend_class_entry *ce, const zend_function *fe,
		const zend_function *proto)
{
	inheritance_status status = zend_do_perform_implementation_check(fe, proto);
	if (UNEXPECTED(status != INHERITANCE_SUCCESS)) {
		if (EXPECTED(status == INHERITANCE_UNRESOLVED)) {
			add_compatibility_obligation(ce, fe, proto);
		} else {
			ZEND_ASSERT(status == INHERITANCE_ERROR);
			emit_incompatible_method_error(fe, proto, status);
		}
	}
}