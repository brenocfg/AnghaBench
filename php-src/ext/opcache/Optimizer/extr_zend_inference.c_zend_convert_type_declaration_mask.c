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
typedef  int uint32_t ;

/* Variables and functions */
 int MAY_BE_ANY ; 
 int MAY_BE_ARRAY ; 
 int MAY_BE_ARRAY_KEY_ANY ; 
 int MAY_BE_ARRAY_OF_ANY ; 
 int MAY_BE_ARRAY_OF_REF ; 
 int MAY_BE_CALLABLE ; 
 int MAY_BE_ITERABLE ; 
 int MAY_BE_NULL ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_STRING ; 
 int MAY_BE_VOID ; 

__attribute__((used)) static uint32_t zend_convert_type_declaration_mask(uint32_t type_mask) {
	uint32_t result_mask = type_mask & MAY_BE_ANY;
	if (type_mask & MAY_BE_VOID) {
		result_mask |= MAY_BE_NULL;
	}
	if (type_mask & MAY_BE_CALLABLE) {
		result_mask |= MAY_BE_STRING|MAY_BE_OBJECT|MAY_BE_ARRAY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
	}
	if (type_mask & MAY_BE_ITERABLE) {
		result_mask |= MAY_BE_OBJECT|MAY_BE_ARRAY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
	}
	if (type_mask & MAY_BE_ARRAY) {
		result_mask |= MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
	}
	return result_mask;
}