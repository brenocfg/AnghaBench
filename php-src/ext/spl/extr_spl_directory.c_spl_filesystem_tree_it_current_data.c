#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_10__ {int /*<<< orphan*/  file_name_len; int /*<<< orphan*/  file_name; } ;
typedef  TYPE_2__ spl_filesystem_object ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__ intern; int /*<<< orphan*/  current; } ;
typedef  TYPE_3__ spl_filesystem_iterator ;

/* Variables and functions */
 scalar_t__ SPL_FILE_DIR_CURRENT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPL_FILE_DIR_CURRENT_AS_FILEINFO ; 
 int /*<<< orphan*/  SPL_FILE_DIR_CURRENT_AS_PATHNAME ; 
 int /*<<< orphan*/  SPL_FS_INFO ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 TYPE_2__* spl_filesystem_iterator_to_object (TYPE_3__*) ; 
 int /*<<< orphan*/  spl_filesystem_object_create_type (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_filesystem_object_get_file_name (TYPE_2__*) ; 

__attribute__((used)) static zval *spl_filesystem_tree_it_current_data(zend_object_iterator *iter)
{
	spl_filesystem_iterator *iterator = (spl_filesystem_iterator *)iter;
	spl_filesystem_object   *object   = spl_filesystem_iterator_to_object(iterator);

	if (SPL_FILE_DIR_CURRENT(object, SPL_FILE_DIR_CURRENT_AS_PATHNAME)) {
		if (Z_ISUNDEF(iterator->current)) {
			spl_filesystem_object_get_file_name(object);
			ZVAL_STRINGL(&iterator->current, object->file_name, object->file_name_len);
		}
		return &iterator->current;
	} else if (SPL_FILE_DIR_CURRENT(object, SPL_FILE_DIR_CURRENT_AS_FILEINFO)) {
		if (Z_ISUNDEF(iterator->current)) {
			spl_filesystem_object_get_file_name(object);
			spl_filesystem_object_create_type(0, object, SPL_FS_INFO, NULL, &iterator->current);
		}
		return &iterator->current;
	} else {
		return &iterator->intern.data;
	}
}