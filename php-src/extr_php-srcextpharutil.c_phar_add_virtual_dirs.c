#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_3__ {int /*<<< orphan*/  virtual_dirs; } ;
typedef  TYPE_1__ phar_archive_data ;

/* Variables and functions */
 int GC_FLAGS (int /*<<< orphan*/ *) ; 
 int GC_PERSISTENT ; 
 int /*<<< orphan*/ * zend_hash_add_empty_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* zend_memrchr (char*,char,size_t) ; 
 int /*<<< orphan*/ * zend_string_init (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zend_string_init_interned (char*,size_t,int) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

void phar_add_virtual_dirs(phar_archive_data *phar, char *filename, size_t filename_len) /* {{{ */
{
	const char *s;
	zend_string *str;
	zval *ret;

	while ((s = zend_memrchr(filename, '/', filename_len))) {
		filename_len = s - filename;
		if (!filename_len) {
			break;
		}
		if (GC_FLAGS(&phar->virtual_dirs) & GC_PERSISTENT) {
			str = zend_string_init_interned(filename, filename_len, 1);
		} else {
			str = zend_string_init(filename, filename_len, 0);
		}
		ret = zend_hash_add_empty_element(&phar->virtual_dirs, str);
		zend_string_release(str);
		if (ret == NULL) {
			break;
		}
	}
}