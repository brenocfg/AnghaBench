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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_init (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor_nogc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void drop_leading_backslash(zval *val) {
	if (Z_STRVAL_P(val)[0] == '\\') {
		zend_string *str = zend_string_init(Z_STRVAL_P(val) + 1, Z_STRLEN_P(val) - 1, 0);
		zval_ptr_dtor_nogc(val);
		ZVAL_STR(val, str);
	}
}