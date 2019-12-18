#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ spl_filesystem_object ;

/* Variables and functions */
 int /*<<< orphan*/  SPL_FILE_OBJECT_SKIP_EMPTY ; 
 scalar_t__ SPL_HAS_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  spl_filesystem_file_free_line (TYPE_1__*) ; 
 scalar_t__ spl_filesystem_file_is_empty_line (TYPE_1__*) ; 
 int spl_filesystem_file_read_line_ex (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static int spl_filesystem_file_read_line(zval * this_ptr, spl_filesystem_object *intern, int silent) /* {{{ */
{
	int ret = spl_filesystem_file_read_line_ex(this_ptr, intern, silent);

	while (SPL_HAS_FLAG(intern->flags, SPL_FILE_OBJECT_SKIP_EMPTY) && ret == SUCCESS && spl_filesystem_file_is_empty_line(intern)) {
		spl_filesystem_file_free_line(intern);
		ret = spl_filesystem_file_read_line_ex(this_ptr, intern, silent);
	}

	return ret;
}