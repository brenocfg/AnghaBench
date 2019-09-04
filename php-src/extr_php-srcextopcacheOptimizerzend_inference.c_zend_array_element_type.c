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
 int MAY_BE_ARRAY_SHIFT ; 
 int MAY_BE_DOUBLE ; 
 int MAY_BE_ERROR ; 
 int MAY_BE_FALSE ; 
 int MAY_BE_LONG ; 
 int MAY_BE_NULL ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_RC1 ; 
 int MAY_BE_RCN ; 
 int MAY_BE_REF ; 
 int MAY_BE_RESOURCE ; 
 int MAY_BE_STRING ; 
 int MAY_BE_TRUE ; 
 int MAY_BE_UNDEF ; 

uint32_t zend_array_element_type(uint32_t t1, int write, int insert)
{
	uint32_t tmp = 0;

	if (t1 & MAY_BE_OBJECT) {
	    if (!write) {
			/* can't be REF  because of ZVAL_COPY_DEREF() usage */
			tmp |= MAY_BE_ANY | MAY_BE_RC1 | MAY_BE_RCN | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
		} else {
			tmp |= MAY_BE_ANY | MAY_BE_REF | MAY_BE_RC1 | MAY_BE_RCN | MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
	    }
	}
	if (t1 & MAY_BE_ARRAY) {
		if (insert) {
			tmp |= MAY_BE_NULL;
		} else {
			tmp |= MAY_BE_NULL | ((t1 & MAY_BE_ARRAY_OF_ANY) >> MAY_BE_ARRAY_SHIFT);
			if (tmp & MAY_BE_ARRAY) {
				tmp |= MAY_BE_ARRAY_KEY_ANY | MAY_BE_ARRAY_OF_ANY | MAY_BE_ARRAY_OF_REF;
			}
			if (t1 & MAY_BE_ARRAY_OF_REF) {
				if (!write) {
					/* can't be REF  because of ZVAL_COPY_DEREF() usage */
					tmp |= MAY_BE_RC1 | MAY_BE_RCN;
				} else {
					tmp |= MAY_BE_REF | MAY_BE_RC1 | MAY_BE_RCN;
				}
			} else if (tmp & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE)) {
				tmp |= MAY_BE_RC1 | MAY_BE_RCN;
			}
		}
	}
	if (t1 & MAY_BE_STRING) {
		tmp |= MAY_BE_STRING | MAY_BE_RC1;
		if (write) {
			tmp |= MAY_BE_NULL;
		}
	}
	if (t1 & (MAY_BE_UNDEF|MAY_BE_NULL|MAY_BE_FALSE)) {
		tmp |= MAY_BE_NULL;
		if (t1 & MAY_BE_ERROR) {
			if (write) {
				tmp |= MAY_BE_ERROR;
			}
		}
	}
	if (t1 & (MAY_BE_TRUE|MAY_BE_LONG|MAY_BE_DOUBLE|MAY_BE_RESOURCE)) {
		tmp |= MAY_BE_NULL;
		if (write) {
			tmp |= MAY_BE_ERROR;
		}
	}
	return tmp;
}