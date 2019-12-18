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
struct TYPE_5__ {scalar_t__ fp_type; int is_modified; char tar_type; scalar_t__ offset; void* flags; scalar_t__ crc32; scalar_t__ compressed_filesize; scalar_t__ uncompressed_filesize; void* old_flags; int /*<<< orphan*/  fp; scalar_t__ is_tar; int /*<<< orphan*/ * link; } ;
typedef  TYPE_1__ phar_entry_info ;
struct TYPE_6__ {int is_modified; } ;
typedef  TYPE_2__ phar_archive_data ;

/* Variables and functions */
 int FAILURE ; 
 void* PHAR_ENT_PERM_DEF_FILE ; 
 scalar_t__ PHAR_MOD ; 
 int SUCCESS ; 
 char TAR_FILE ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_fopen_tmpfile () ; 
 int /*<<< orphan*/  php_stream_truncate_set_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*) ; 

int phar_create_writeable_entry(phar_archive_data *phar, phar_entry_info *entry, char **error) /* {{{ */
{
	if (entry->fp_type == PHAR_MOD) {
		/* already newly created, truncate */
		php_stream_truncate_set_size(entry->fp, 0);

		entry->old_flags = entry->flags;
		entry->is_modified = 1;
		phar->is_modified = 1;
		/* reset file size */
		entry->uncompressed_filesize = 0;
		entry->compressed_filesize = 0;
		entry->crc32 = 0;
		entry->flags = PHAR_ENT_PERM_DEF_FILE;
		entry->fp_type = PHAR_MOD;
		entry->offset = 0;
		return SUCCESS;
	}

	if (error) {
		*error = NULL;
	}

	/* open a new temp file for writing */
	if (entry->link) {
		efree(entry->link);
		entry->link = NULL;
		entry->tar_type = (entry->is_tar ? TAR_FILE : '\0');
	}

	entry->fp = php_stream_fopen_tmpfile();

	if (!entry->fp) {
		if (error) {
			spprintf(error, 0, "phar error: unable to create temporary file");
		}
		return FAILURE;
	}

	entry->old_flags = entry->flags;
	entry->is_modified = 1;
	phar->is_modified = 1;
	/* reset file size */
	entry->uncompressed_filesize = 0;
	entry->compressed_filesize = 0;
	entry->crc32 = 0;
	entry->flags = PHAR_ENT_PERM_DEF_FILE;
	entry->fp_type = PHAR_MOD;
	entry->offset = 0;
	return SUCCESS;
}