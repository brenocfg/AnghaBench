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
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  zend_empty_array ; 

__attribute__((used)) static HashTable *com_properties_get(zend_object *object)
{
	/* TODO: use type-info to get all the names and values ?
	 * DANGER: if we do that, there is a strong possibility for
	 * infinite recursion when the hash is displayed via var_dump().
	 * Perhaps it is best to leave it un-implemented.
	 */
	return &zend_empty_array;
}