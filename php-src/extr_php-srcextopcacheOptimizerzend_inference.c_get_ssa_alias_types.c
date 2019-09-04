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
typedef  scalar_t__ zend_ssa_alias_kind ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ HTTP_RESPONSE_HEADER_ALIAS ; 
 int MAY_BE_ANY ; 
 int MAY_BE_ARRAY ; 
 int MAY_BE_ARRAY_KEY_ANY ; 
 int MAY_BE_ARRAY_KEY_LONG ; 
 int MAY_BE_ARRAY_OF_ANY ; 
 int MAY_BE_ARRAY_OF_REF ; 
 int MAY_BE_ARRAY_OF_STRING ; 
 int MAY_BE_RC1 ; 
 int MAY_BE_RCN ; 
 int MAY_BE_REF ; 
 int MAY_BE_UNDEF ; 

__attribute__((used)) static uint32_t get_ssa_alias_types(zend_ssa_alias_kind alias) {
	if (alias == HTTP_RESPONSE_HEADER_ALIAS) {
		return MAY_BE_ARRAY | MAY_BE_ARRAY_KEY_LONG | MAY_BE_ARRAY_OF_STRING | MAY_BE_RC1 | MAY_BE_RCN;
	} else {
		return MAY_BE_UNDEF | MAY_BE_RC1 | MAY_BE_RCN | MAY_BE_REF | MAY_BE_ANY | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
	}
}