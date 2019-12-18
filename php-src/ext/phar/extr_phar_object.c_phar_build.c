#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_20__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_32__ {TYPE_3__* funcs; } ;
typedef  TYPE_8__ zend_object_iterator ;
struct TYPE_33__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_9__ zend_class_entry ;
typedef  int zend_bool ;
struct _phar_t {size_t l; char* b; int /*<<< orphan*/  ret; int /*<<< orphan*/  fp; TYPE_12__* p; TYPE_9__* c; } ;
struct TYPE_29__ {int /*<<< orphan*/  d_name; } ;
struct TYPE_30__ {TYPE_5__ entry; } ;
struct TYPE_31__ {TYPE_6__ dir; } ;
struct TYPE_21__ {char* file_name; TYPE_7__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_10__ spl_filesystem_object ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_22__ {TYPE_2__* internal_file; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_11__ phar_entry_data ;
struct TYPE_23__ {TYPE_1__* archive; } ;
typedef  TYPE_12__ phar_archive_object ;
struct TYPE_28__ {int /*<<< orphan*/  offset; } ;
struct TYPE_27__ {int /*<<< orphan*/  (* get_current_key ) (TYPE_8__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* get_current_data ) (TYPE_8__*) ;} ;
struct TYPE_26__ {scalar_t__ fp_type; void* offset_abs; void* offset; size_t uncompressed_filesize; size_t compressed_filesize; int /*<<< orphan*/ * fp; } ;
struct TYPE_25__ {TYPE_4__* handlers; } ;
struct TYPE_24__ {int /*<<< orphan*/  fname_len; int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SLASH ; 
 scalar_t__ EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_IS_DIR ; 
#define  IS_OBJECT 133 
#define  IS_RESOURCE 132 
#define  IS_STRING 131 
 int const IS_TRUE ; 
 scalar_t__ PHAR_MOD ; 
 scalar_t__ PHAR_UFP ; 
 int /*<<< orphan*/  PHP_STREAM_COPY_ALL ; 
#define  SPL_FS_DIR 130 
#define  SPL_FS_FILE 129 
#define  SPL_FS_INFO 128 
 int STREAM_MUST_SEEK ; 
 int ZEND_HASH_APPLY_KEEP ; 
 int ZEND_HASH_APPLY_STOP ; 
 char* ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 TYPE_20__* Z_OBJ_P (int /*<<< orphan*/ *) ; 
 size_t Z_STRLEN (int /*<<< orphan*/ ) ; 
 size_t Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int const Z_TYPE (int /*<<< orphan*/ ) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrndup (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  exception ; 
 char* expand_filepath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  instanceof_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  phar_entry_delref (TYPE_11__*) ; 
 TYPE_11__* phar_get_or_create_entry_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,char*,int /*<<< orphan*/ ,char**,int) ; 
 scalar_t__ php_check_open_basedir (char*) ; 
 int /*<<< orphan*/  php_stat (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_copy_to_stream_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  php_stream_from_zval_no_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_stream_open_wrapper (char*,char*,int,int /*<<< orphan*/ **) ; 
 void* php_stream_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spl_ce_BadMethodCallException ; 
 int /*<<< orphan*/  spl_ce_SplFileInfo ; 
 int /*<<< orphan*/  spl_ce_UnexpectedValueException ; 
 char* spl_filesystem_object_get_path (TYPE_10__*,int /*<<< orphan*/ *) ; 
 size_t spprintf (char**,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phar_build(zend_object_iterator *iter, void *puser) /* {{{ */
{
	zval *value;
	zend_bool close_fp = 1;
	struct _phar_t *p_obj = (struct _phar_t*) puser;
	size_t str_key_len, base_len = p_obj->l;
	phar_entry_data *data;
	php_stream *fp;
	size_t fname_len;
	size_t contents_len;
	char *fname, *error = NULL, *base = p_obj->b, *save = NULL, *temp = NULL;
	zend_string *opened;
	char *str_key;
	zend_class_entry *ce = p_obj->c;
	phar_archive_object *phar_obj = p_obj->p;

	value = iter->funcs->get_current_data(iter);

	if (EG(exception)) {
		return ZEND_HASH_APPLY_STOP;
	}

	if (!value) {
		/* failure in get_current_data */
		zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Iterator %s returned no value", ZSTR_VAL(ce->name));
		return ZEND_HASH_APPLY_STOP;
	}

	switch (Z_TYPE_P(value)) {
		case IS_STRING:
			break;
		case IS_RESOURCE:
			php_stream_from_zval_no_verify(fp, value);

			if (!fp) {
				zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "Iterator %s returned an invalid stream handle", ZSTR_VAL(ce->name));
				return ZEND_HASH_APPLY_STOP;
			}

			if (iter->funcs->get_current_key) {
				zval key;
				iter->funcs->get_current_key(iter, &key);

				if (EG(exception)) {
					return ZEND_HASH_APPLY_STOP;
				}

				if (Z_TYPE(key) != IS_STRING) {
					zval_ptr_dtor(&key);
					zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Iterator %s returned an invalid key (must return a string)", ZSTR_VAL(ce->name));
					return ZEND_HASH_APPLY_STOP;
				}

				str_key_len = Z_STRLEN(key);
				str_key = estrndup(Z_STRVAL(key), str_key_len);

				save = str_key;
				zval_ptr_dtor_str(&key);
			} else {
				zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Iterator %s returned an invalid key (must return a string)", ZSTR_VAL(ce->name));
				return ZEND_HASH_APPLY_STOP;
			}

			close_fp = 0;
			opened = zend_string_init("[stream]", sizeof("[stream]") - 1, 0);
			goto after_open_fp;
		case IS_OBJECT:
			if (instanceof_function(Z_OBJCE_P(value), spl_ce_SplFileInfo)) {
				char *test = NULL;
				zval dummy;
				spl_filesystem_object *intern = (spl_filesystem_object*)((char*)Z_OBJ_P(value) - Z_OBJ_P(value)->handlers->offset);

				if (!base_len) {
					zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "Iterator %s returns an SplFileInfo object, so base directory must be specified", ZSTR_VAL(ce->name));
					return ZEND_HASH_APPLY_STOP;
				}

				switch (intern->type) {
					case SPL_FS_DIR:
						test = spl_filesystem_object_get_path(intern, NULL);
						fname_len = spprintf(&fname, 0, "%s%c%s", test, DEFAULT_SLASH, intern->u.dir.entry.d_name);
						php_stat(fname, fname_len, FS_IS_DIR, &dummy);

						if (Z_TYPE(dummy) == IS_TRUE) {
							/* ignore directories */
							efree(fname);
							return ZEND_HASH_APPLY_KEEP;
						}

						test = expand_filepath(fname, NULL);
						efree(fname);

						if (test) {
							fname = test;
							fname_len = strlen(fname);
						} else {
							zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Could not resolve file path");
							return ZEND_HASH_APPLY_STOP;
						}

						save = fname;
						goto phar_spl_fileinfo;
					case SPL_FS_INFO:
					case SPL_FS_FILE:
						fname = expand_filepath(intern->file_name, NULL);
						if (!fname) {
							zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Could not resolve file path");
							return ZEND_HASH_APPLY_STOP;
						}

						fname_len = strlen(fname);
						save = fname;
						goto phar_spl_fileinfo;
				}
			}
			/* fall-through */
		default:
			zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Iterator %s returned an invalid value (must return a string)", ZSTR_VAL(ce->name));
			return ZEND_HASH_APPLY_STOP;
	}

	fname = Z_STRVAL_P(value);
	fname_len = Z_STRLEN_P(value);

phar_spl_fileinfo:
	if (base_len) {
		temp = expand_filepath(base, NULL);
		if (!temp) {
			zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Could not resolve file path");
			if (save) {
				efree(save);
			}
			return ZEND_HASH_APPLY_STOP;
		}

		base = temp;
		base_len = strlen(base);

		if (strstr(fname, base)) {
			str_key_len = fname_len - base_len;

			if (str_key_len <= 0) {
				if (save) {
					efree(save);
					efree(temp);
				}
				return ZEND_HASH_APPLY_KEEP;
			}

			str_key = fname + base_len;

			if (*str_key == '/' || *str_key == '\\') {
				str_key++;
				str_key_len--;
			}

		} else {
			zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Iterator %s returned a path \"%s\" that is not in the base directory \"%s\"", ZSTR_VAL(ce->name), fname, base);

			if (save) {
				efree(save);
				efree(temp);
			}

			return ZEND_HASH_APPLY_STOP;
		}
	} else {
		if (iter->funcs->get_current_key) {
			zval key;
			iter->funcs->get_current_key(iter, &key);

			if (EG(exception)) {
				return ZEND_HASH_APPLY_STOP;
			}

			if (Z_TYPE(key) != IS_STRING) {
				zval_ptr_dtor(&key);
				zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Iterator %s returned an invalid key (must return a string)", ZSTR_VAL(ce->name));
				return ZEND_HASH_APPLY_STOP;
			}

			str_key_len = Z_STRLEN(key);
			str_key = estrndup(Z_STRVAL(key), str_key_len);

			save = str_key;
			zval_ptr_dtor_str(&key);
		} else {
			zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Iterator %s returned an invalid key (must return a string)", ZSTR_VAL(ce->name));
			return ZEND_HASH_APPLY_STOP;
		}
	}

	if (php_check_open_basedir(fname)) {
		zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Iterator %s returned a path \"%s\" that open_basedir prevents opening", ZSTR_VAL(ce->name), fname);

		if (save) {
			efree(save);
		}

		if (temp) {
			efree(temp);
		}

		return ZEND_HASH_APPLY_STOP;
	}

	/* try to open source file, then create internal phar file and copy contents */
	fp = php_stream_open_wrapper(fname, "rb", STREAM_MUST_SEEK|0, &opened);

	if (!fp) {
		zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0, "Iterator %s returned a file that could not be opened \"%s\"", ZSTR_VAL(ce->name), fname);

		if (save) {
			efree(save);
		}

		if (temp) {
			efree(temp);
		}

		return ZEND_HASH_APPLY_STOP;
	}
after_open_fp:
	if (str_key_len >= sizeof(".phar")-1 && !memcmp(str_key, ".phar", sizeof(".phar")-1)) {
		/* silently skip any files that would be added to the magic .phar directory */
		if (save) {
			efree(save);
		}

		if (temp) {
			efree(temp);
		}

		if (opened) {
			zend_string_release_ex(opened, 0);
		}

		if (close_fp) {
			php_stream_close(fp);
		}

		return ZEND_HASH_APPLY_KEEP;
	}

	if (!(data = phar_get_or_create_entry_data(phar_obj->archive->fname, phar_obj->archive->fname_len, str_key, str_key_len, "w+b", 0, &error, 1))) {
		zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "Entry %s cannot be created: %s", str_key, error);
		efree(error);

		if (save) {
			efree(save);
		}

		if (opened) {
			zend_string_release_ex(opened, 0);
		}

		if (temp) {
			efree(temp);
		}

		if (close_fp) {
			php_stream_close(fp);
		}

		return ZEND_HASH_APPLY_STOP;

	} else {
		if (error) {
			efree(error);
		}
		/* convert to PHAR_UFP */
		if (data->internal_file->fp_type == PHAR_MOD) {
			php_stream_close(data->internal_file->fp);
		}

		data->internal_file->fp = NULL;
		data->internal_file->fp_type = PHAR_UFP;
		data->internal_file->offset_abs = data->internal_file->offset = php_stream_tell(p_obj->fp);
		data->fp = NULL;
		php_stream_copy_to_stream_ex(fp, p_obj->fp, PHP_STREAM_COPY_ALL, &contents_len);
		data->internal_file->uncompressed_filesize = data->internal_file->compressed_filesize =
			php_stream_tell(p_obj->fp) - data->internal_file->offset;
	}

	if (close_fp) {
		php_stream_close(fp);
	}

	add_assoc_str(p_obj->ret, str_key, opened);

	if (save) {
		efree(save);
	}

	if (temp) {
		efree(temp);
	}

	data->internal_file->compressed_filesize = data->internal_file->uncompressed_filesize = contents_len;
	phar_entry_delref(data);

	return ZEND_HASH_APPLY_KEEP;
}