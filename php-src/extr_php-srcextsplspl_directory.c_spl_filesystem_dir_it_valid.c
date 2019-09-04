#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_6__ {char* d_name; } ;
struct TYPE_7__ {TYPE_1__ entry; } ;
struct TYPE_8__ {TYPE_2__ dir; } ;
struct TYPE_9__ {TYPE_3__ u; } ;
typedef  TYPE_4__ spl_filesystem_object ;
typedef  int /*<<< orphan*/  spl_filesystem_iterator ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 TYPE_4__* spl_filesystem_iterator_to_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_filesystem_dir_it_valid(zend_object_iterator *iter)
{
	spl_filesystem_object *object = spl_filesystem_iterator_to_object((spl_filesystem_iterator *)iter);

	return object->u.dir.entry.d_name[0] != '\0' ? SUCCESS : FAILURE;
}