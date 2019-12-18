#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_9__ {int /*<<< orphan*/  d_name; } ;
struct TYPE_11__ {TYPE_1__ entry; scalar_t__ dirp; scalar_t__ index; } ;
struct TYPE_10__ {TYPE_3__ dir; } ;
struct TYPE_12__ {TYPE_2__ u; } ;
typedef  TYPE_4__ spl_filesystem_object ;
struct TYPE_13__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_5__ spl_filesystem_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_rewinddir (scalar_t__) ; 
 int /*<<< orphan*/  spl_filesystem_dir_read (TYPE_4__*) ; 
 scalar_t__ spl_filesystem_is_dot (int /*<<< orphan*/ ) ; 
 TYPE_4__* spl_filesystem_iterator_to_object (TYPE_5__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_filesystem_tree_it_rewind(zend_object_iterator *iter)
{
	spl_filesystem_iterator *iterator = (spl_filesystem_iterator *)iter;
	spl_filesystem_object   *object   = spl_filesystem_iterator_to_object(iterator);

	object->u.dir.index = 0;
	if (object->u.dir.dirp) {
		php_stream_rewinddir(object->u.dir.dirp);
	}
	do {
		spl_filesystem_dir_read(object);
	} while (spl_filesystem_is_dot(object->u.dir.entry.d_name));
	if (!Z_ISUNDEF(iterator->current)) {
		zval_ptr_dtor(&iterator->current);
		ZVAL_UNDEF(&iterator->current);
	}
}