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
typedef  int /*<<< orphan*/  zend_function ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ zend_arg_info ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_TYPE_IS_SET (int /*<<< orphan*/ ) ; 
 int zend_do_perform_type_hint_check (int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/  const*,TYPE_1__*) ; 

__attribute__((used)) static int zend_do_perform_arg_type_hint_check(const zend_function *fe, zend_arg_info *fe_arg_info, const zend_function *proto, zend_arg_info *proto_arg_info) /* {{{ */
{
	if (!ZEND_TYPE_IS_SET(fe_arg_info->type)) {
		/* Child with no type is always compatible */
		return 1;
	}

	if (!ZEND_TYPE_IS_SET(proto_arg_info->type)) {
		/* Child defines a type, but parent doesn't, violates LSP */
		return 0;
	}

	return zend_do_perform_type_hint_check(fe, fe_arg_info, proto, proto_arg_info);
}