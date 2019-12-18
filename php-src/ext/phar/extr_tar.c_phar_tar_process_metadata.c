#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_6__ {size_t uncompressed_filesize; int filename_len; int filename; int /*<<< orphan*/  metadata; TYPE_1__* phar; } ;
typedef  TYPE_2__ phar_entry_info ;
struct TYPE_5__ {int /*<<< orphan*/  manifest; int /*<<< orphan*/  metadata; } ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  memcmp (int,char*,int) ; 
 int phar_parse_metadata (char**,int /*<<< orphan*/ *,size_t) ; 
 size_t php_stream_read (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 size_t php_stream_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ safe_emalloc (int,size_t,int) ; 
 TYPE_2__* zend_hash_str_find_ptr (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int phar_tar_process_metadata(phar_entry_info *entry, php_stream *fp) /* {{{ */
{
	char *metadata;
	size_t save = php_stream_tell(fp), read;
	phar_entry_info *mentry;

	metadata = (char *) safe_emalloc(1, entry->uncompressed_filesize, 1);

	read = php_stream_read(fp, metadata, entry->uncompressed_filesize);
	if (read != entry->uncompressed_filesize) {
		efree(metadata);
		php_stream_seek(fp, save, SEEK_SET);
		return FAILURE;
	}

	if (phar_parse_metadata(&metadata, &entry->metadata, entry->uncompressed_filesize) == FAILURE) {
		/* if not valid serialized data, it is a regular string */
		efree(metadata);
		php_stream_seek(fp, save, SEEK_SET);
		return FAILURE;
	}

	if (entry->filename_len == sizeof(".phar/.metadata.bin")-1 && !memcmp(entry->filename, ".phar/.metadata.bin", sizeof(".phar/.metadata.bin")-1)) {
		entry->phar->metadata = entry->metadata;
		ZVAL_UNDEF(&entry->metadata);
	} else if (entry->filename_len >= sizeof(".phar/.metadata/") + sizeof("/.metadata.bin") - 1 && NULL != (mentry = zend_hash_str_find_ptr(&(entry->phar->manifest), entry->filename + sizeof(".phar/.metadata/") - 1, entry->filename_len - (sizeof("/.metadata.bin") - 1 + sizeof(".phar/.metadata/") - 1)))) {
		/* transfer this metadata to the entry it refers */
		mentry->metadata = entry->metadata;
		ZVAL_UNDEF(&entry->metadata);
	}

	efree(metadata);
	php_stream_seek(fp, save, SEEK_SET);
	return SUCCESS;
}