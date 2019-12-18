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
typedef  int /*<<< orphan*/  php_serialize_data_t ;
struct TYPE_8__ {int /*<<< orphan*/ * s; } ;
struct TYPE_7__ {scalar_t__ fp_type; int is_modified; int /*<<< orphan*/  filename_len; int /*<<< orphan*/  filename; TYPE_1__* phar; TYPE_3__ metadata_str; int /*<<< orphan*/ * fp; scalar_t__ offset_abs; scalar_t__ offset; scalar_t__ compressed_filesize; scalar_t__ uncompressed_filesize; } ;
typedef  TYPE_2__ phar_entry_info ;
struct TYPE_6__ {int /*<<< orphan*/  manifest; } ;

/* Variables and functions */
 scalar_t__ PHAR_MOD ; 
 int /*<<< orphan*/  PHP_VAR_SERIALIZE_DESTROY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_VAR_SERIALIZE_INIT (int /*<<< orphan*/ ) ; 
 int ZEND_HASH_APPLY_KEEP ; 
 int ZEND_HASH_APPLY_STOP ; 
 scalar_t__ ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_stream_fopen_tmpfile () ; 
 scalar_t__ php_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  php_var_serialize (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_3__*) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  zend_hash_str_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int phar_tar_setmetadata(zval *metadata, phar_entry_info *entry, char **error) /* {{{ */
{
	php_serialize_data_t metadata_hash;

	if (entry->metadata_str.s) {
		smart_str_free(&entry->metadata_str);
	}

	entry->metadata_str.s = NULL;
	PHP_VAR_SERIALIZE_INIT(metadata_hash);
	php_var_serialize(&entry->metadata_str, metadata, &metadata_hash);
	PHP_VAR_SERIALIZE_DESTROY(metadata_hash);
	entry->uncompressed_filesize = entry->compressed_filesize = entry->metadata_str.s ? ZSTR_LEN(entry->metadata_str.s) : 0;

	if (entry->fp && entry->fp_type == PHAR_MOD) {
		php_stream_close(entry->fp);
	}

	entry->fp_type = PHAR_MOD;
	entry->is_modified = 1;
	entry->fp = php_stream_fopen_tmpfile();
	entry->offset = entry->offset_abs = 0;
	if (entry->fp == NULL) {
		spprintf(error, 0, "phar error: unable to create temporary file");
		return -1;
	}
	if (ZSTR_LEN(entry->metadata_str.s) != php_stream_write(entry->fp, ZSTR_VAL(entry->metadata_str.s), ZSTR_LEN(entry->metadata_str.s))) {
		spprintf(error, 0, "phar tar error: unable to write metadata to magic metadata file \"%s\"", entry->filename);
		zend_hash_str_del(&(entry->phar->manifest), entry->filename, entry->filename_len);
		return ZEND_HASH_APPLY_STOP;
	}

	return ZEND_HASH_APPLY_KEEP;
}