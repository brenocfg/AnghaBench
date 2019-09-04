#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_bool ;
struct TYPE_4__ {int ar_flags; int /*<<< orphan*/  array; } ;
typedef  TYPE_1__ spl_array_object ;

/* Variables and functions */
 scalar_t__ IS_OBJECT ; 
 int SPL_ARRAY_IS_SELF ; 
 int SPL_ARRAY_USE_OTHER ; 
 TYPE_1__* Z_SPLARRAY_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zend_bool spl_array_is_object(spl_array_object *intern) /* {{{ */
{
	while (intern->ar_flags & SPL_ARRAY_USE_OTHER) {
		intern = Z_SPLARRAY_P(&intern->array);
	}
	return (intern->ar_flags & SPL_ARRAY_IS_SELF) || Z_TYPE(intern->array) == IS_OBJECT;
}