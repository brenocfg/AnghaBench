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
typedef  int RAnalClassAttrType ;

/* Variables and functions */
#define  R_ANAL_CLASS_ATTR_TYPE_BASE 130 
#define  R_ANAL_CLASS_ATTR_TYPE_METHOD 129 
#define  R_ANAL_CLASS_ATTR_TYPE_VTABLE 128 

__attribute__((used)) static const char *attr_type_id(RAnalClassAttrType attr_type) {
	switch (attr_type) {
	case R_ANAL_CLASS_ATTR_TYPE_METHOD:
		return "method";
	case R_ANAL_CLASS_ATTR_TYPE_VTABLE:
		return "vtable";
	case R_ANAL_CLASS_ATTR_TYPE_BASE:
		return "base";
	default:
		return NULL;
	}
}