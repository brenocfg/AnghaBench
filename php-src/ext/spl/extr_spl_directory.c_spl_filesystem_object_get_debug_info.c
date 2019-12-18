#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_10__ {char* open_mode; int open_mode_len; char delimiter; char enclosure; } ;
struct TYPE_9__ {char* sub_path; int sub_path_len; int /*<<< orphan*/  dirp; } ;
struct TYPE_11__ {TYPE_2__ file; TYPE_1__ dir; } ;
struct TYPE_13__ {int /*<<< orphan*/  properties; } ;
struct TYPE_12__ {char* file_name; size_t file_name_len; scalar_t__ type; char* _path; int _path_len; TYPE_3__ u; TYPE_8__ std; } ;
typedef  TYPE_4__ spl_filesystem_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 scalar_t__ SPL_FS_DIR ; 
 scalar_t__ SPL_FS_FILE ; 
 int /*<<< orphan*/  ZVAL_EMPTY_STRING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_FALSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  php_glob_stream_ops ; 
 scalar_t__ php_stream_is (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebuild_object_properties (TYPE_8__*) ; 
 int /*<<< orphan*/  spl_ce_DirectoryIterator ; 
 int /*<<< orphan*/  spl_ce_RecursiveDirectoryIterator ; 
 int /*<<< orphan*/  spl_ce_SplFileInfo ; 
 int /*<<< orphan*/  spl_ce_SplFileObject ; 
 TYPE_4__* spl_filesystem_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_filesystem_object_get_path (TYPE_4__*,size_t*) ; 
 char* spl_filesystem_object_get_pathname (TYPE_4__*,size_t*) ; 
 int /*<<< orphan*/ * spl_gen_private_prop_name (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * zend_array_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_symtable_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HashTable *spl_filesystem_object_get_debug_info(zend_object *object, int *is_temp) /* {{{ */
{
	spl_filesystem_object *intern = spl_filesystem_from_obj(object);
	zval tmp;
	HashTable *rv;
	zend_string *pnstr;
	char *path;
	size_t  path_len;
	char stmp[2];

	*is_temp = 1;

	if (!intern->std.properties) {
		rebuild_object_properties(&intern->std);
	}

	rv = zend_array_dup(intern->std.properties);

	pnstr = spl_gen_private_prop_name(spl_ce_SplFileInfo, "pathName", sizeof("pathName")-1);
	path = spl_filesystem_object_get_pathname(intern, &path_len);
	ZVAL_STRINGL(&tmp, path ? path : "", path_len);
	zend_symtable_update(rv, pnstr, &tmp);
	zend_string_release_ex(pnstr, 0);

	if (intern->file_name) {
		pnstr = spl_gen_private_prop_name(spl_ce_SplFileInfo, "fileName", sizeof("fileName")-1);
		spl_filesystem_object_get_path(intern, &path_len);

		if (path_len && path_len < intern->file_name_len) {
			ZVAL_STRINGL(&tmp, intern->file_name + path_len + 1, intern->file_name_len - (path_len + 1));
		} else {
			ZVAL_STRINGL(&tmp, intern->file_name, intern->file_name_len);
		}
		zend_symtable_update(rv, pnstr, &tmp);
		zend_string_release_ex(pnstr, 0);
	}
	if (intern->type == SPL_FS_DIR) {
#ifdef HAVE_GLOB
		pnstr = spl_gen_private_prop_name(spl_ce_DirectoryIterator, "glob", sizeof("glob")-1);
		if (php_stream_is(intern->u.dir.dirp ,&php_glob_stream_ops)) {
			ZVAL_STRINGL(&tmp, intern->_path, intern->_path_len);
		} else {
			ZVAL_FALSE(&tmp);
		}
		zend_symtable_update(rv, pnstr, &tmp);
		zend_string_release_ex(pnstr, 0);
#endif
		pnstr = spl_gen_private_prop_name(spl_ce_RecursiveDirectoryIterator, "subPathName", sizeof("subPathName")-1);
		if (intern->u.dir.sub_path) {
			ZVAL_STRINGL(&tmp, intern->u.dir.sub_path, intern->u.dir.sub_path_len);
		} else {
			ZVAL_EMPTY_STRING(&tmp);
		}
		zend_symtable_update(rv, pnstr, &tmp);
		zend_string_release_ex(pnstr, 0);
	}
	if (intern->type == SPL_FS_FILE) {
		pnstr = spl_gen_private_prop_name(spl_ce_SplFileObject, "openMode", sizeof("openMode")-1);
		ZVAL_STRINGL(&tmp, intern->u.file.open_mode, intern->u.file.open_mode_len);
		zend_symtable_update(rv, pnstr, &tmp);
		zend_string_release_ex(pnstr, 0);
		stmp[1] = '\0';
		stmp[0] = intern->u.file.delimiter;
		pnstr = spl_gen_private_prop_name(spl_ce_SplFileObject, "delimiter", sizeof("delimiter")-1);
		ZVAL_STRINGL(&tmp, stmp, 1);
		zend_symtable_update(rv, pnstr, &tmp);
		zend_string_release_ex(pnstr, 0);
		stmp[0] = intern->u.file.enclosure;
		pnstr = spl_gen_private_prop_name(spl_ce_SplFileObject, "enclosure", sizeof("enclosure")-1);
		ZVAL_STRINGL(&tmp, stmp, 1);
		zend_symtable_update(rv, pnstr, &tmp);
		zend_string_release_ex(pnstr, 0);
	}

	return rv;
}