#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_11__ {int st_mode; } ;
struct TYPE_13__ {TYPE_1__ sb; } ;
typedef  TYPE_3__ php_stream_statbuf ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_14__ {TYPE_5__* phar; TYPE_2__* internal_file; int /*<<< orphan*/  fp; } ;
typedef  TYPE_4__ phar_entry_data ;
struct TYPE_15__ {int /*<<< orphan*/  fname_len; int /*<<< orphan*/  fname; } ;
typedef  TYPE_5__ phar_archive_data ;
typedef  int mode_t ;
struct TYPE_12__ {size_t compressed_filesize; size_t uncompressed_filesize; int flags; int /*<<< orphan*/  is_dir; } ;

/* Variables and functions */
 int PHAR_ENT_PERM_MASK ; 
 int /*<<< orphan*/  PHP_STREAM_COPY_ALL ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  phar_ce_PharException ; 
 int /*<<< orphan*/  phar_entry_delref (TYPE_4__*) ; 
 int /*<<< orphan*/  phar_flush (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 TYPE_4__* phar_get_or_create_entry_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,char*,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  php_stream_copy_to_stream_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  php_stream_from_zval_no_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int php_stream_stat (int /*<<< orphan*/ *,TYPE_3__*) ; 
 size_t php_stream_write (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  spl_ce_BadMethodCallException ; 
 int umask (int) ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void phar_add_file(phar_archive_data **pphar, char *filename, size_t filename_len, char *cont_str, size_t cont_len, zval *zresource)
{
	size_t start_pos=0;
	char *error;
	size_t contents_len;
	phar_entry_data *data;
	php_stream *contents_file = NULL;
	php_stream_statbuf ssb;
#ifdef PHP_WIN32
	char *save_filename;
	ALLOCA_FLAG(filename_use_heap)
#endif

	if (filename_len >= sizeof(".phar")-1) {
		start_pos = '/' == filename[0]; /* account for any leading slash: multiple-leads handled elsewhere */
		if (!memcmp(&filename[start_pos], ".phar", sizeof(".phar")-1) && (filename[start_pos+5] == '/' || filename[start_pos+5] == '\\' || filename[start_pos+5] == '\0')) {
			zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "Cannot create any files in magic \".phar\" directory");
			return;
		}
	}

#ifdef PHP_WIN32
	save_filename = filename;
	if (memchr(filename, '\\', filename_len)) {
		filename = do_alloca(filename_len + 1, filename_use_heap);
		memcpy(filename, save_filename, filename_len);
		filename[filename_len] = '\0';
	}
#endif

	if (!(data = phar_get_or_create_entry_data((*pphar)->fname, (*pphar)->fname_len, filename, filename_len, "w+b", 0, &error, 1))) {
		if (error) {
			zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "Entry %s does not exist and cannot be created: %s", filename, error);
			efree(error);
		} else {
			zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "Entry %s does not exist and cannot be created", filename);
		}
		goto finish;
	} else {
		if (error) {
			efree(error);
		}

		if (!data->internal_file->is_dir) {
			if (cont_str) {
				contents_len = php_stream_write(data->fp, cont_str, cont_len);
				if (contents_len != cont_len) {
					zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "Entry %s could not be written to", filename);
					goto finish;
				}
			} else {
				if (!(php_stream_from_zval_no_verify(contents_file, zresource))) {
					zend_throw_exception_ex(spl_ce_BadMethodCallException, 0, "Entry %s could not be written to", filename);
					goto finish;
				}
				php_stream_copy_to_stream_ex(contents_file, data->fp, PHP_STREAM_COPY_ALL, &contents_len);
			}
			data->internal_file->compressed_filesize = data->internal_file->uncompressed_filesize = contents_len;
		}

		if (contents_file != NULL && php_stream_stat(contents_file, &ssb) != -1) {
			data->internal_file->flags = ssb.sb.st_mode & PHAR_ENT_PERM_MASK ;
		} else {
#ifndef _WIN32
			mode_t mask;
			mask = umask(0);
			umask(mask);
			data->internal_file->flags &= ~mask;
#endif
		}

		/* check for copy-on-write */
		if (pphar[0] != data->phar) {
			*pphar = data->phar;
		}
		phar_entry_delref(data);
		phar_flush(*pphar, 0, 0, 0, &error);

		if (error) {
			zend_throw_exception_ex(phar_ce_PharException, 0, "%s", error);
			efree(error);
		}
	}

finish: ;
#ifdef PHP_WIN32
	if (filename != save_filename) {
		free_alloca(filename, filename_use_heap);
		filename = save_filename;
	}
#endif
}