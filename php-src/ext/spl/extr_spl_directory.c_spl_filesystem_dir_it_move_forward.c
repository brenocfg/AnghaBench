#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_7__ {TYPE_1__ dir; } ;
struct TYPE_8__ {int /*<<< orphan*/ * file_name; TYPE_2__ u; } ;
typedef  TYPE_3__ spl_filesystem_object ;
typedef  int /*<<< orphan*/  spl_filesystem_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_filesystem_dir_read (TYPE_3__*) ; 
 TYPE_3__* spl_filesystem_iterator_to_object (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_filesystem_dir_it_move_forward(zend_object_iterator *iter)
{
	spl_filesystem_object *object = spl_filesystem_iterator_to_object((spl_filesystem_iterator *)iter);

	object->u.dir.index++;
	spl_filesystem_dir_read(object);
	if (object->file_name) {
		efree(object->file_name);
		object->file_name = NULL;
	}
}