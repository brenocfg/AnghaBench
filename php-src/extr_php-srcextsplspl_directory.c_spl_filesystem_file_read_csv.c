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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {size_t current_line_len; int /*<<< orphan*/  current_zval; int /*<<< orphan*/  stream; int /*<<< orphan*/  current_line; } ;
struct TYPE_7__ {TYPE_1__ file; } ;
struct TYPE_8__ {TYPE_2__ u; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ spl_filesystem_object ;

/* Variables and functions */
 int /*<<< orphan*/  SPL_FILE_OBJECT_SKIP_EMPTY ; 
 scalar_t__ SPL_HAS_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_COPY_DEREF (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 char* estrndup (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  php_fgetcsv (int /*<<< orphan*/ ,char,char,int,size_t,char*,int /*<<< orphan*/ *) ; 
 int spl_filesystem_file_read (TYPE_3__*,int) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_filesystem_file_read_csv(spl_filesystem_object *intern, char delimiter, char enclosure, int escape, zval *return_value) /* {{{ */
{
	int ret = SUCCESS;
	zval *value;

	do {
		ret = spl_filesystem_file_read(intern, 1);
	} while (ret == SUCCESS && !intern->u.file.current_line_len && SPL_HAS_FLAG(intern->flags, SPL_FILE_OBJECT_SKIP_EMPTY));

	if (ret == SUCCESS) {
		size_t buf_len = intern->u.file.current_line_len;
		char *buf = estrndup(intern->u.file.current_line, buf_len);

		if (!Z_ISUNDEF(intern->u.file.current_zval)) {
			zval_ptr_dtor(&intern->u.file.current_zval);
			ZVAL_UNDEF(&intern->u.file.current_zval);
		}

		php_fgetcsv(intern->u.file.stream, delimiter, enclosure, escape, buf_len, buf, &intern->u.file.current_zval);
		if (return_value) {
			value = &intern->u.file.current_zval;
			ZVAL_COPY_DEREF(return_value, value);
		}
	}
	return ret;
}