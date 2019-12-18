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
typedef  int /*<<< orphan*/  collator_compare_func_t ;

/* Variables and functions */
#define  COLLATOR_SORT_NUMERIC 130 
#define  COLLATOR_SORT_REGULAR 129 
#define  COLLATOR_SORT_STRING 128 
 int /*<<< orphan*/  collator_icu_compare_function ; 
 int /*<<< orphan*/  collator_numeric_compare_function ; 
 int /*<<< orphan*/  collator_regular_compare_function ; 

__attribute__((used)) static collator_compare_func_t collator_get_compare_function( const zend_long sort_flags )
{
	collator_compare_func_t func;

	switch( sort_flags )
	{
		case COLLATOR_SORT_NUMERIC:
			func = collator_numeric_compare_function;
			break;

		case COLLATOR_SORT_STRING:
			func = collator_icu_compare_function;
			break;

		case COLLATOR_SORT_REGULAR:
		default:
			func = collator_regular_compare_function;
			break;
	}

	return func;
}