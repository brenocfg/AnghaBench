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
typedef  int zend_long ;

/* Variables and functions */
 int CIT_CALL_TOSTRING ; 
 int CIT_TOSTRING_USE_CURRENT ; 
 int CIT_TOSTRING_USE_INNER ; 
 int CIT_TOSTRING_USE_KEY ; 
 int FAILURE ; 
 int SUCCESS ; 

__attribute__((used)) static inline int spl_cit_check_flags(zend_long flags)
{
	zend_long cnt = 0;

	cnt += (flags & CIT_CALL_TOSTRING) ? 1 : 0;
	cnt += (flags & CIT_TOSTRING_USE_KEY) ? 1 : 0;
	cnt += (flags & CIT_TOSTRING_USE_CURRENT) ? 1 : 0;
	cnt += (flags & CIT_TOSTRING_USE_INNER) ? 1 : 0;

	return cnt <= 1 ? SUCCESS : FAILURE;
}