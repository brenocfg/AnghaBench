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
typedef  int zend_bool ;

/* Variables and functions */
 int IS_CV ; 
 int IS_TMP_VAR ; 
 int IS_VAR ; 

__attribute__((used)) static inline zend_bool is_var_type(zend_uchar type) {
	return (type & (IS_CV|IS_VAR|IS_TMP_VAR)) != 0;
}