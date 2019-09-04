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
 int MAY_BE_ARRAY ; 
 int MAY_BE_ARRAY_KEY_ANY ; 
 int MAY_BE_ARRAY_OF_ANY ; 
 int MAY_BE_ARRAY_OF_REF ; 

__attribute__((used)) static inline uint32_t mask_for_type_check(uint32_t type) {
	if (type & MAY_BE_ARRAY) {
		return MAY_BE_ARRAY|MAY_BE_ARRAY_KEY_ANY|MAY_BE_ARRAY_OF_ANY|MAY_BE_ARRAY_OF_REF;
	} else {
		return type;
	}
}