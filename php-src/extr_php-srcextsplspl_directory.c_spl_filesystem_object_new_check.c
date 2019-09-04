#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * handlers; } ;
typedef  TYPE_1__ zend_object ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_6__ {TYPE_1__ std; } ;
typedef  TYPE_2__ spl_filesystem_object ;

/* Variables and functions */
 TYPE_2__* spl_filesystem_from_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_filesystem_object_check_handlers ; 
 int /*<<< orphan*/  spl_filesystem_object_new_ex (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_object *spl_filesystem_object_new_check(zend_class_entry *class_type)
{
	spl_filesystem_object *ret = spl_filesystem_from_obj(spl_filesystem_object_new_ex(class_type));
	ret->std.handlers = &spl_filesystem_object_check_handlers;
	return &ret->std;
}