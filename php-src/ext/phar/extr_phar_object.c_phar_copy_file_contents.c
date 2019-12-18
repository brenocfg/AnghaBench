#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_off_t ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_10__ {scalar_t__ fp_type; int /*<<< orphan*/  offset; int /*<<< orphan*/ * fp; int /*<<< orphan*/ * cfp; int /*<<< orphan*/  filename; TYPE_1__* phar; int /*<<< orphan*/  uncompressed_filesize; } ;
typedef  TYPE_2__ phar_entry_info ;
struct TYPE_9__ {int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ PHAR_FP ; 
 scalar_t__ PHAR_MOD ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  phar_get_efp (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* phar_get_link_source (TYPE_2__*) ; 
 scalar_t__ phar_open_entry_fp (TYPE_2__*,char**,int) ; 
 int /*<<< orphan*/  phar_seek_efp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ php_stream_copy_to_stream_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_ce_UnexpectedValueException ; 
 int /*<<< orphan*/  zend_throw_exception_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int phar_copy_file_contents(phar_entry_info *entry, php_stream *fp) /* {{{ */
{
	char *error;
	zend_off_t offset;
	phar_entry_info *link;

	if (FAILURE == phar_open_entry_fp(entry, &error, 1)) {
		if (error) {
			zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0,
				"Cannot convert phar archive \"%s\", unable to open entry \"%s\" contents: %s", entry->phar->fname, entry->filename, error);
			efree(error);
		} else {
			zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0,
				"Cannot convert phar archive \"%s\", unable to open entry \"%s\" contents", entry->phar->fname, entry->filename);
		}
		return FAILURE;
	}

	/* copy old contents in entirety */
	phar_seek_efp(entry, 0, SEEK_SET, 0, 1);
	offset = php_stream_tell(fp);
	link = phar_get_link_source(entry);

	if (!link) {
		link = entry;
	}

	if (SUCCESS != php_stream_copy_to_stream_ex(phar_get_efp(link, 0), fp, link->uncompressed_filesize, NULL)) {
		zend_throw_exception_ex(spl_ce_UnexpectedValueException, 0,
			"Cannot convert phar archive \"%s\", unable to copy entry \"%s\" contents", entry->phar->fname, entry->filename);
		return FAILURE;
	}

	if (entry->fp_type == PHAR_MOD) {
		/* save for potential restore on error */
		entry->cfp = entry->fp;
		entry->fp = NULL;
	}

	/* set new location of file contents */
	entry->fp_type = PHAR_FP;
	entry->offset = offset;
	return SUCCESS;
}