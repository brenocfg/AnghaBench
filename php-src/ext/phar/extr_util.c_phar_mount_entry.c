#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int st_mode; int /*<<< orphan*/  st_size; } ;
struct TYPE_8__ {TYPE_1__ sb; } ;
typedef  TYPE_2__ php_stream_statbuf ;
struct TYPE_9__ {char* filename; size_t filename_len; char* tmp; int is_mounted; int is_crc_checked; int is_dir; int flags; int /*<<< orphan*/  compressed_filesize; int /*<<< orphan*/  uncompressed_filesize; int /*<<< orphan*/  fp_type; TYPE_4__* phar; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ phar_entry_info ;
struct TYPE_10__ {int /*<<< orphan*/  manifest; int /*<<< orphan*/  mounted_dirs; } ;
typedef  TYPE_4__ phar_archive_data ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  PHAR_TMP ; 
 scalar_t__ SUCCESS ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  efree (char*) ; 
 void* estrndup (char*,size_t) ; 
 char* expand_filepath (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 scalar_t__ pcr_is_ok ; 
 scalar_t__ phar_path_check (char**,size_t*,char const**) ; 
 int /*<<< orphan*/  phar_unixify_path_separators (char*,size_t) ; 
 scalar_t__ php_check_open_basedir (char*) ; 
 scalar_t__ php_stream_stat_path (char*,TYPE_2__*) ; 
 int /*<<< orphan*/ * zend_hash_str_add_mem (int /*<<< orphan*/ *,char*,size_t,void*,int) ; 
 int /*<<< orphan*/ * zend_hash_str_add_ptr (int /*<<< orphan*/ *,char*,size_t,char*) ; 

int phar_mount_entry(phar_archive_data *phar, char *filename, size_t filename_len, char *path, size_t path_len) /* {{{ */
{
	phar_entry_info entry = {0};
	php_stream_statbuf ssb;
	int is_phar;
	const char *err;

	if (phar_path_check(&path, &path_len, &err) > pcr_is_ok) {
		return FAILURE;
	}

	if (path_len >= sizeof(".phar")-1 && !memcmp(path, ".phar", sizeof(".phar")-1)) {
		/* no creating magic phar files by mounting them */
		return FAILURE;
	}

	is_phar = (filename_len > 7 && !memcmp(filename, "phar://", 7));

	entry.phar = phar;
	entry.filename = estrndup(path, path_len);
#ifdef PHP_WIN32
	phar_unixify_path_separators(entry.filename, path_len);
#endif
	entry.filename_len = path_len;
	if (is_phar) {
		entry.tmp = estrndup(filename, filename_len);
	} else {
		entry.tmp = expand_filepath(filename, NULL);
		if (!entry.tmp) {
			entry.tmp = estrndup(filename, filename_len);
		}
	}
	filename = entry.tmp;

	/* only check openbasedir for files, not for phar streams */
	if (!is_phar && php_check_open_basedir(filename)) {
		efree(entry.tmp);
		efree(entry.filename);
		return FAILURE;
	}

	entry.is_mounted = 1;
	entry.is_crc_checked = 1;
	entry.fp_type = PHAR_TMP;

	if (SUCCESS != php_stream_stat_path(filename, &ssb)) {
		efree(entry.tmp);
		efree(entry.filename);
		return FAILURE;
	}

	if (ssb.sb.st_mode & S_IFDIR) {
		entry.is_dir = 1;
		if (NULL == zend_hash_str_add_ptr(&phar->mounted_dirs, entry.filename, path_len, entry.filename)) {
			/* directory already mounted */
			efree(entry.tmp);
			efree(entry.filename);
			return FAILURE;
		}
	} else {
		entry.is_dir = 0;
		entry.uncompressed_filesize = entry.compressed_filesize = ssb.sb.st_size;
	}

	entry.flags = ssb.sb.st_mode;

	if (NULL != zend_hash_str_add_mem(&phar->manifest, entry.filename, path_len, (void*)&entry, sizeof(phar_entry_info))) {
		return SUCCESS;
	}

	efree(entry.tmp);
	efree(entry.filename);
	return FAILURE;
}