#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  checksum; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; int /*<<< orphan*/  linkname; int /*<<< orphan*/  typeflag; int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; int /*<<< orphan*/  prefix; } ;
typedef  TYPE_1__ tar_header ;
struct _phar_pass_tar_info {int /*<<< orphan*/  free_ufp; int /*<<< orphan*/  free_fp; int /*<<< orphan*/  new; scalar_t__ error; } ;
struct TYPE_9__ {scalar_t__ fp_refcount; char* filename; int filename_len; int flags; int uncompressed_filesize; int timestamp; char* link; int crc32; int fp_type; size_t offset; size_t offset_abs; int /*<<< orphan*/ * fp; TYPE_7__* phar; scalar_t__ is_modified; void* header_offset; int /*<<< orphan*/  tar_type; scalar_t__ is_deleted; scalar_t__ is_mounted; } ;
typedef  TYPE_2__ phar_entry_info ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_10__ {int /*<<< orphan*/ * ufp; int /*<<< orphan*/ * fp; int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 int PHAR_ENT_PERM_MASK ; 
#define  PHAR_FP 129 
 int PHAR_MOD ; 
#define  PHAR_UFP 128 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SUCCESS ; 
 int ZEND_HASH_APPLY_KEEP ; 
 int ZEND_HASH_APPLY_REMOVE ; 
 int ZEND_HASH_APPLY_STOP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phar_add_virtual_dirs (TYPE_7__*,char*,int) ; 
 int /*<<< orphan*/  phar_get_efp (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ phar_open_entry_fp (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int phar_seek_efp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phar_tar_checksum (char*,int) ; 
 scalar_t__ phar_tar_octal (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 
 scalar_t__ php_stream_copy_to_stream_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* php_stream_tell (int /*<<< orphan*/ ) ; 
 int php_stream_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spprintf (scalar_t__,int,char*,int /*<<< orphan*/ ,char*) ; 
 int strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int phar_tar_writeheaders_int(phar_entry_info *entry, void *argument) /* {{{ */
{
	tar_header header;
	size_t pos;
	struct _phar_pass_tar_info *fp = (struct _phar_pass_tar_info *)argument;
	char padding[512];

	if (entry->is_mounted) {
		return ZEND_HASH_APPLY_KEEP;
	}

	if (entry->is_deleted) {
		if (entry->fp_refcount <= 0) {
			return ZEND_HASH_APPLY_REMOVE;
		} else {
			/* we can't delete this in-memory until it is closed */
			return ZEND_HASH_APPLY_KEEP;
		}
	}

	phar_add_virtual_dirs(entry->phar, entry->filename, entry->filename_len);
	memset((char *) &header, 0, sizeof(header));

	if (entry->filename_len > 100) {
		char *boundary;
		if (entry->filename_len > 256) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, filename \"%s\" is too long for tar file format", entry->phar->fname, entry->filename);
			}
			return ZEND_HASH_APPLY_STOP;
		}
		boundary = entry->filename + entry->filename_len - 101;
		while (*boundary && *boundary != '/') {
			++boundary;
		}
		if (!*boundary || ((boundary - entry->filename) > 155)) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, filename \"%s\" is too long for tar file format", entry->phar->fname, entry->filename);
			}
			return ZEND_HASH_APPLY_STOP;
		}
		memcpy(header.prefix, entry->filename, boundary - entry->filename);
		memcpy(header.name, boundary + 1, entry->filename_len - (boundary + 1 - entry->filename));
	} else {
		memcpy(header.name, entry->filename, entry->filename_len);
	}

	phar_tar_octal(header.mode, entry->flags & PHAR_ENT_PERM_MASK, sizeof(header.mode)-1);

	if (FAILURE == phar_tar_octal(header.size, entry->uncompressed_filesize, sizeof(header.size)-1)) {
		if (fp->error) {
			spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, filename \"%s\" is too large for tar file format", entry->phar->fname, entry->filename);
		}
		return ZEND_HASH_APPLY_STOP;
	}

	if (FAILURE == phar_tar_octal(header.mtime, entry->timestamp, sizeof(header.mtime)-1)) {
		if (fp->error) {
			spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, file modification time of file \"%s\" is too large for tar file format", entry->phar->fname, entry->filename);
		}
		return ZEND_HASH_APPLY_STOP;
	}

	/* calc checksum */
	header.typeflag = entry->tar_type;

	if (entry->link) {
		if (strlcpy(header.linkname, entry->link, sizeof(header.linkname)) >= sizeof(header.linkname)) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, link \"%s\" is too long for format", entry->phar->fname, entry->link);
			}
			return ZEND_HASH_APPLY_STOP;
		}
	}

	memcpy(header.magic, "ustar", sizeof("ustar")-1);
	memcpy(header.version, "00", sizeof("00")-1);
	memcpy(header.checksum, "        ", sizeof("        ")-1);
	entry->crc32 = phar_tar_checksum((char *)&header, sizeof(header));

	if (FAILURE == phar_tar_octal(header.checksum, entry->crc32, sizeof(header.checksum)-1)) {
		if (fp->error) {
			spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, checksum of file \"%s\" is too large for tar file format", entry->phar->fname, entry->filename);
		}
		return ZEND_HASH_APPLY_STOP;
	}

	/* write header */
	entry->header_offset = php_stream_tell(fp->new);

	if (sizeof(header) != php_stream_write(fp->new, (char *) &header, sizeof(header))) {
		if (fp->error) {
			spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, header for  file \"%s\" could not be written", entry->phar->fname, entry->filename);
		}
		return ZEND_HASH_APPLY_STOP;
	}

	pos = php_stream_tell(fp->new); /* save start of file within tar */

	/* write contents */
	if (entry->uncompressed_filesize) {
		if (FAILURE == phar_open_entry_fp(entry, fp->error, 0)) {
			return ZEND_HASH_APPLY_STOP;
		}

		if (-1 == phar_seek_efp(entry, 0, SEEK_SET, 0, 0)) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, contents of file \"%s\" could not be written, seek failed", entry->phar->fname, entry->filename);
			}
			return ZEND_HASH_APPLY_STOP;
		}

		if (SUCCESS != php_stream_copy_to_stream_ex(phar_get_efp(entry, 0), fp->new, entry->uncompressed_filesize, NULL)) {
			if (fp->error) {
				spprintf(fp->error, 4096, "tar-based phar \"%s\" cannot be created, contents of file \"%s\" could not be written", entry->phar->fname, entry->filename);
			}
			return ZEND_HASH_APPLY_STOP;
		}

		memset(padding, 0, 512);
		php_stream_write(fp->new, padding, ((entry->uncompressed_filesize +511)&~511) - entry->uncompressed_filesize);
	}

	if (!entry->is_modified && entry->fp_refcount) {
		/* open file pointers refer to this fp, do not free the stream */
		switch (entry->fp_type) {
			case PHAR_FP:
				fp->free_fp = 0;
				break;
			case PHAR_UFP:
				fp->free_ufp = 0;
			default:
				break;
		}
	}

	entry->is_modified = 0;

	if (entry->fp_type == PHAR_MOD && entry->fp != entry->phar->fp && entry->fp != entry->phar->ufp) {
		if (!entry->fp_refcount) {
			php_stream_close(entry->fp);
		}
		entry->fp = NULL;
	}

	entry->fp_type = PHAR_FP;

	/* note new location within tar */
	entry->offset = entry->offset_abs = pos;
	return ZEND_HASH_APPLY_KEEP;
}