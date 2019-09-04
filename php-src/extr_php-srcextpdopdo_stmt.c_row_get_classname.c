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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;

/* Variables and functions */
 int /*<<< orphan*/ * zend_string_init (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *row_get_classname(const zend_object *object)
{
	return zend_string_init("PDORow", sizeof("PDORow") - 1, 0);
}