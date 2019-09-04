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
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_uchar ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  int zend_bool ;

/* Variables and functions */
#define  IS_DOUBLE 131 
#define  IS_LONG 130 
#define  IS_STRING 129 
 int /*<<< orphan*/  ZVAL_BOOL (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  _IS_BOOL 128 
 int /*<<< orphan*/  zend_parse_arg_bool_weak (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zend_parse_arg_double_weak (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  zend_parse_arg_long_weak (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zend_parse_arg_str_weak (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool zend_verify_weak_scalar_type_hint(zend_uchar type_hint, zval *arg)
{
	switch (type_hint) {
		case _IS_BOOL: {
			zend_bool dest;

			if (!zend_parse_arg_bool_weak(arg, &dest)) {
				return 0;
			}
			zval_ptr_dtor(arg);
			ZVAL_BOOL(arg, dest);
			return 1;
		}
		case IS_LONG: {
			zend_long dest;

			if (!zend_parse_arg_long_weak(arg, &dest)) {
				return 0;
			}
			zval_ptr_dtor(arg);
			ZVAL_LONG(arg, dest);
			return 1;
		}
		case IS_DOUBLE: {
			double dest;

			if (!zend_parse_arg_double_weak(arg, &dest)) {
				return 0;
			}
			zval_ptr_dtor(arg);
			ZVAL_DOUBLE(arg, dest);
			return 1;
		}
		case IS_STRING: {
			zend_string *dest;

			/* on success "arg" is converted to IS_STRING */
			return zend_parse_arg_str_weak(arg, &dest);
		}
		default:
			return 0;
	}
}