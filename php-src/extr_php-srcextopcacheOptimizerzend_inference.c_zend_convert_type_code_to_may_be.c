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
typedef  int zend_uchar ;
typedef  int uint32_t ;

/* Variables and functions */
#define  IS_ARRAY 132 
#define  IS_CALLABLE 131 
#define  IS_ITERABLE 130 
 int IS_REFERENCE ; 
#define  IS_VOID 129 
 int MAY_BE_ARRAY ; 
 int MAY_BE_ARRAY_KEY_ANY ; 
 int MAY_BE_ARRAY_OF_ANY ; 
 int MAY_BE_ARRAY_OF_REF ; 
 int MAY_BE_FALSE ; 
 int MAY_BE_NULL ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_STRING ; 
 int MAY_BE_TRUE ; 
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
#define  _IS_BOOL 128 

__attribute__((used)) static uint32_t zend_convert_type_code_to_may_be(zend_uchar type_code) {
	switch (type_code) {
		case IS_VOID:
			return MAY_BE_NULL;
		case IS_CALLABLE:
			return MAY_BE_STRING|MAY_BE_OBJECT|MAY_BE_ARRAY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
		case IS_ITERABLE:
			return MAY_BE_OBJECT|MAY_BE_ARRAY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
		case IS_ARRAY:
			return MAY_BE_ARRAY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
		case _IS_BOOL:
			return MAY_BE_TRUE|MAY_BE_FALSE;
		default:
			ZEND_ASSERT(type_code < IS_REFERENCE);
			return 1 << type_code;
	}
}