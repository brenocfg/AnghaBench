#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fn_flags; int /*<<< orphan*/  function_name; } ;
struct TYPE_9__ {TYPE_1__ internal_function; } ;
typedef  TYPE_2__ zend_function ;

/* Variables and functions */
 int ZEND_ACC_CALL_VIA_TRAMPOLINE ; 
 TYPE_2__* emalloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_function *_copy_function(zend_function *fptr) /* {{{ */
{
	if (fptr
		&& (fptr->internal_function.fn_flags & ZEND_ACC_CALL_VIA_TRAMPOLINE))
	{
		zend_function *copy_fptr;
		copy_fptr = emalloc(sizeof(zend_function));
		memcpy(copy_fptr, fptr, sizeof(zend_function));
		copy_fptr->internal_function.function_name = zend_string_copy(fptr->internal_function.function_name);
		return copy_fptr;
	} else {
		/* no copy needed */
		return fptr;
	}
}