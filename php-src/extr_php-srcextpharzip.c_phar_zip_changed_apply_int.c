#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_24__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_off_t ;
typedef  scalar_t__ uint32_t ;
struct _phar_zip_pass {int /*<<< orphan*/  error; TYPE_1__* centralfp; TYPE_1__* filefp; TYPE_1__* old; int /*<<< orphan*/  free_ufp; int /*<<< orphan*/  free_fp; } ;
typedef  int /*<<< orphan*/  php_stream_filter ;
struct TYPE_26__ {int /*<<< orphan*/  writefilters; } ;
typedef  TYPE_1__ php_stream ;
typedef  int /*<<< orphan*/  php_serialize_data_t ;
struct TYPE_28__ {char* tag; int /*<<< orphan*/ * comment_len; int /*<<< orphan*/  crc32; int /*<<< orphan*/  compsize; int /*<<< orphan*/  uncompsize; int /*<<< orphan*/  offset; int /*<<< orphan*/ * filename_len; int /*<<< orphan*/  datestamp; int /*<<< orphan*/  timestamp; int /*<<< orphan*/ * compressed; int /*<<< orphan*/ * perms; int /*<<< orphan*/ * size; int /*<<< orphan*/ * extra_len; int /*<<< orphan*/  signature; } ;
typedef  TYPE_2__ phar_zip_unix3 ;
typedef  TYPE_2__ phar_zip_file_header ;
typedef  TYPE_2__ phar_zip_central_dir_file ;
struct TYPE_30__ {int /*<<< orphan*/ * s; } ;
struct TYPE_29__ {scalar_t__ fp_refcount; char* filename; int filename_len; int flags; int is_modified; int fp_type; int old_flags; scalar_t__ uncompressed_filesize; scalar_t__ crc32; scalar_t__ compressed_filesize; int offset_abs; int header_offset; int offset; TYPE_6__ metadata_str; TYPE_24__* phar; TYPE_1__* fp; scalar_t__ is_dir; TYPE_1__* cfp; int /*<<< orphan*/  metadata; int /*<<< orphan*/  timestamp; scalar_t__ is_deleted; scalar_t__ is_mounted; } ;
typedef  TYPE_5__ phar_entry_info ;
typedef  int /*<<< orphan*/  perms ;
typedef  int /*<<< orphan*/  local ;
typedef  int /*<<< orphan*/  central ;
struct TYPE_27__ {int /*<<< orphan*/  fname; TYPE_1__* ufp; TYPE_1__* fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILURE ; 
 scalar_t__ IS_UNDEF ; 
 int PHAR_ENT_COMPRESSED_BZ2 ; 
 int PHAR_ENT_COMPRESSED_GZ ; 
 int PHAR_ENT_COMPRESSION_MASK ; 
 int PHAR_ENT_PERM_MASK ; 
#define  PHAR_FP 129 
 int PHAR_MOD ; 
 int /*<<< orphan*/  PHAR_SET_16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PHAR_SET_32 (int /*<<< orphan*/ ,scalar_t__) ; 
#define  PHAR_UFP 128 
 int PHAR_ZIP_COMP_BZIP2 ; 
 int PHAR_ZIP_COMP_DEFLATE ; 
 int /*<<< orphan*/  PHP_VAR_SERIALIZE_DESTROY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHP_VAR_SERIALIZE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SUCCESS ; 
 int ZEND_HASH_APPLY_KEEP ; 
 int ZEND_HASH_APPLY_REMOVE ; 
 int ZEND_HASH_APPLY_STOP ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phar_add_virtual_dirs (TYPE_24__*,char*,int) ; 
 int /*<<< orphan*/  phar_compress_filter (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* phar_get_efp (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ phar_open_entry_fp (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phar_seek_efp (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phar_zip_u2d_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_close (TYPE_1__*) ; 
 scalar_t__ php_stream_copy_to_stream_ex (TYPE_1__*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_filter_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_stream_filter_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_filter_flush (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  php_stream_filter_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  php_stream_flush (TYPE_1__*) ; 
 TYPE_1__* php_stream_fopen_tmpfile () ; 
 int /*<<< orphan*/  php_stream_getc (TYPE_1__*) ; 
 int /*<<< orphan*/  php_stream_rewind (TYPE_1__*) ; 
 int php_stream_seek (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ php_stream_tell (TYPE_1__*) ; 
 int php_stream_write (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  php_var_serialize (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_6__*) ; 
 int /*<<< orphan*/  spprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int phar_zip_changed_apply_int(phar_entry_info *entry, void *arg) /* {{{ */
{
	phar_zip_file_header local;
	phar_zip_unix3 perms;
	phar_zip_central_dir_file central;
	struct _phar_zip_pass *p;
	uint32_t newcrc32;
	zend_off_t offset;
	int not_really_modified = 0;
	p = (struct _phar_zip_pass*) arg;

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
	memset(&local, 0, sizeof(local));
	memset(&central, 0, sizeof(central));
	memset(&perms, 0, sizeof(perms));
	strncpy(local.signature, "PK\3\4", 4);
	strncpy(central.signature, "PK\1\2", 4);
	PHAR_SET_16(central.extra_len, sizeof(perms));
	PHAR_SET_16(local.extra_len, sizeof(perms));
	perms.tag[0] = 'n';
	perms.tag[1] = 'u';
	PHAR_SET_16(perms.size, sizeof(perms) - 4);
	PHAR_SET_16(perms.perms, entry->flags & PHAR_ENT_PERM_MASK);
	{
		uint32_t crc = (uint32_t) ~0;
		CRC32(crc, perms.perms[0]);
		CRC32(crc, perms.perms[1]);
		PHAR_SET_32(perms.crc32, ~crc);
	}

	if (entry->flags & PHAR_ENT_COMPRESSED_GZ) {
		PHAR_SET_16(central.compressed, PHAR_ZIP_COMP_DEFLATE);
		PHAR_SET_16(local.compressed, PHAR_ZIP_COMP_DEFLATE);
	}

	if (entry->flags & PHAR_ENT_COMPRESSED_BZ2) {
		PHAR_SET_16(central.compressed, PHAR_ZIP_COMP_BZIP2);
		PHAR_SET_16(local.compressed, PHAR_ZIP_COMP_BZIP2);
	}

	/* do not use PHAR_GET_16 on either field of the next line */
	phar_zip_u2d_time(entry->timestamp, local.timestamp, local.datestamp);
	memcpy(central.timestamp, local.timestamp, sizeof(local.timestamp));
	memcpy(central.datestamp, local.datestamp, sizeof(local.datestamp));
	PHAR_SET_16(central.filename_len, entry->filename_len + (entry->is_dir ? 1 : 0));
	PHAR_SET_16(local.filename_len, entry->filename_len + (entry->is_dir ? 1 : 0));
	PHAR_SET_32(central.offset, php_stream_tell(p->filefp));

	/* do extra field for perms later */
	if (entry->is_modified) {
		uint32_t loc;
		php_stream_filter *filter;
		php_stream *efp;

		if (entry->is_dir) {
			entry->is_modified = 0;
			if (entry->fp_type == PHAR_MOD && entry->fp != entry->phar->fp && entry->fp != entry->phar->ufp) {
				php_stream_close(entry->fp);
				entry->fp = NULL;
				entry->fp_type = PHAR_FP;
			}
			goto continue_dir;
		}

		if (FAILURE == phar_open_entry_fp(entry, p->error, 0)) {
			spprintf(p->error, 0, "unable to open file contents of file \"%s\" in zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}

		/* we can be modified and already be compressed, such as when chmod() is executed */
		if (entry->flags & PHAR_ENT_COMPRESSION_MASK && (entry->old_flags == entry->flags || !entry->old_flags)) {
			not_really_modified = 1;
			goto is_compressed;
		}

		if (-1 == phar_seek_efp(entry, 0, SEEK_SET, 0, 0)) {
			spprintf(p->error, 0, "unable to seek to start of file \"%s\" to zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}

		efp = phar_get_efp(entry, 0);
		newcrc32 = ~0;

		for (loc = 0;loc < entry->uncompressed_filesize; ++loc) {
			CRC32(newcrc32, php_stream_getc(efp));
		}

		entry->crc32 = ~newcrc32;
		PHAR_SET_32(central.uncompsize, entry->uncompressed_filesize);
		PHAR_SET_32(local.uncompsize, entry->uncompressed_filesize);

		if (!(entry->flags & PHAR_ENT_COMPRESSION_MASK)) {
			/* not compressed */
			entry->compressed_filesize = entry->uncompressed_filesize;
			PHAR_SET_32(central.compsize, entry->uncompressed_filesize);
			PHAR_SET_32(local.compsize, entry->uncompressed_filesize);
			goto not_compressed;
		}

		filter = php_stream_filter_create(phar_compress_filter(entry, 0), NULL, 0);

		if (!filter) {
			if (entry->flags & PHAR_ENT_COMPRESSED_GZ) {
				spprintf(p->error, 0, "unable to gzip compress file \"%s\" to zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			} else {
				spprintf(p->error, 0, "unable to bzip2 compress file \"%s\" to zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			}
			return ZEND_HASH_APPLY_STOP;
		}

		/* create new file that holds the compressed version */
		/* work around inability to specify freedom in write and strictness
		in read count */
		entry->cfp = php_stream_fopen_tmpfile();

		if (!entry->cfp) {
			spprintf(p->error, 0, "unable to create temporary file for file \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}

		php_stream_flush(efp);

		if (-1 == phar_seek_efp(entry, 0, SEEK_SET, 0, 0)) {
			spprintf(p->error, 0, "unable to seek to start of file \"%s\" to zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}

		php_stream_filter_append((&entry->cfp->writefilters), filter);

		if (SUCCESS != php_stream_copy_to_stream_ex(efp, entry->cfp, entry->uncompressed_filesize, NULL)) {
			spprintf(p->error, 0, "unable to copy compressed file contents of file \"%s\" while creating new phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}

		php_stream_filter_flush(filter, 1);
		php_stream_flush(entry->cfp);
		php_stream_filter_remove(filter, 1);
		php_stream_seek(entry->cfp, 0, SEEK_END);
		entry->compressed_filesize = (uint32_t) php_stream_tell(entry->cfp);
		PHAR_SET_32(central.compsize, entry->compressed_filesize);
		PHAR_SET_32(local.compsize, entry->compressed_filesize);
		/* generate crc on compressed file */
		php_stream_rewind(entry->cfp);
		entry->old_flags = entry->flags;
		entry->is_modified = 1;
	} else {
is_compressed:
		PHAR_SET_32(central.uncompsize, entry->uncompressed_filesize);
		PHAR_SET_32(local.uncompsize, entry->uncompressed_filesize);
		PHAR_SET_32(central.compsize, entry->compressed_filesize);
		PHAR_SET_32(local.compsize, entry->compressed_filesize);
		if (p->old) {
			if (-1 == php_stream_seek(p->old, entry->offset_abs, SEEK_SET)) {
				spprintf(p->error, 0, "unable to seek to start of file \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
				return ZEND_HASH_APPLY_STOP;
			}
		}
	}
not_compressed:
	PHAR_SET_32(central.crc32, entry->crc32);
	PHAR_SET_32(local.crc32, entry->crc32);
continue_dir:
	/* set file metadata */
	if (Z_TYPE(entry->metadata) != IS_UNDEF) {
		php_serialize_data_t metadata_hash;

		if (entry->metadata_str.s) {
			smart_str_free(&entry->metadata_str);
		}
		entry->metadata_str.s = NULL;
		PHP_VAR_SERIALIZE_INIT(metadata_hash);
		php_var_serialize(&entry->metadata_str, &entry->metadata, &metadata_hash);
		PHP_VAR_SERIALIZE_DESTROY(metadata_hash);
		PHAR_SET_16(central.comment_len, ZSTR_LEN(entry->metadata_str.s));
	}

	entry->header_offset = php_stream_tell(p->filefp);
	offset = entry->header_offset + sizeof(local) + entry->filename_len + (entry->is_dir ? 1 : 0) + sizeof(perms);

	if (sizeof(local) != php_stream_write(p->filefp, (char *)&local, sizeof(local))) {
		spprintf(p->error, 0, "unable to write local file header of file \"%s\" to zip-based phar \"%s\"", entry->filename, entry->phar->fname);
		return ZEND_HASH_APPLY_STOP;
	}

	if (sizeof(central) != php_stream_write(p->centralfp, (char *)&central, sizeof(central))) {
		spprintf(p->error, 0, "unable to write central directory entry for file \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
		return ZEND_HASH_APPLY_STOP;
	}

	if (entry->is_dir) {
		if (entry->filename_len != php_stream_write(p->filefp, entry->filename, entry->filename_len)) {
			spprintf(p->error, 0, "unable to write filename to local directory entry for directory \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}

		if (1 != php_stream_write(p->filefp, "/", 1)) {
			spprintf(p->error, 0, "unable to write filename to local directory entry for directory \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}

		if (entry->filename_len != php_stream_write(p->centralfp, entry->filename, entry->filename_len)) {
			spprintf(p->error, 0, "unable to write filename to central directory entry for directory \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}

		if (1 != php_stream_write(p->centralfp, "/", 1)) {
			spprintf(p->error, 0, "unable to write filename to central directory entry for directory \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}
	} else {
		if (entry->filename_len != php_stream_write(p->filefp, entry->filename, entry->filename_len)) {
			spprintf(p->error, 0, "unable to write filename to local directory entry for file \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}

		if (entry->filename_len != php_stream_write(p->centralfp, entry->filename, entry->filename_len)) {
			spprintf(p->error, 0, "unable to write filename to central directory entry for file \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}
	}

	if (sizeof(perms) != php_stream_write(p->filefp, (char *)&perms, sizeof(perms))) {
		spprintf(p->error, 0, "unable to write local extra permissions file header of file \"%s\" to zip-based phar \"%s\"", entry->filename, entry->phar->fname);
		return ZEND_HASH_APPLY_STOP;
	}

	if (sizeof(perms) != php_stream_write(p->centralfp, (char *)&perms, sizeof(perms))) {
		spprintf(p->error, 0, "unable to write central extra permissions file header of file \"%s\" to zip-based phar \"%s\"", entry->filename, entry->phar->fname);
		return ZEND_HASH_APPLY_STOP;
	}

	if (!not_really_modified && entry->is_modified) {
		if (entry->cfp) {
			if (SUCCESS != php_stream_copy_to_stream_ex(entry->cfp, p->filefp, entry->compressed_filesize, NULL)) {
				spprintf(p->error, 0, "unable to write compressed contents of file \"%s\" in zip-based phar \"%s\"", entry->filename, entry->phar->fname);
				return ZEND_HASH_APPLY_STOP;
			}

			php_stream_close(entry->cfp);
			entry->cfp = NULL;
		} else {
			if (FAILURE == phar_open_entry_fp(entry, p->error, 0)) {
				return ZEND_HASH_APPLY_STOP;
			}

			phar_seek_efp(entry, 0, SEEK_SET, 0, 0);

			if (SUCCESS != php_stream_copy_to_stream_ex(phar_get_efp(entry, 0), p->filefp, entry->uncompressed_filesize, NULL)) {
				spprintf(p->error, 0, "unable to write contents of file \"%s\" in zip-based phar \"%s\"", entry->filename, entry->phar->fname);
				return ZEND_HASH_APPLY_STOP;
			}
		}

		if (entry->fp_type == PHAR_MOD && entry->fp != entry->phar->fp && entry->fp != entry->phar->ufp && entry->fp_refcount == 0) {
			php_stream_close(entry->fp);
		}

		entry->is_modified = 0;
	} else {
		entry->is_modified = 0;
		if (entry->fp_refcount) {
			/* open file pointers refer to this fp, do not free the stream */
			switch (entry->fp_type) {
				case PHAR_FP:
					p->free_fp = 0;
					break;
				case PHAR_UFP:
					p->free_ufp = 0;
				default:
					break;
			}
		}

		if (!entry->is_dir && entry->compressed_filesize && SUCCESS != php_stream_copy_to_stream_ex(p->old, p->filefp, entry->compressed_filesize, NULL)) {
			spprintf(p->error, 0, "unable to copy contents of file \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			return ZEND_HASH_APPLY_STOP;
		}
	}

	entry->fp = NULL;
	entry->offset = entry->offset_abs = offset;
	entry->fp_type = PHAR_FP;

	if (entry->metadata_str.s) {
		if (ZSTR_LEN(entry->metadata_str.s) != php_stream_write(p->centralfp, ZSTR_VAL(entry->metadata_str.s), ZSTR_LEN(entry->metadata_str.s))) {
			spprintf(p->error, 0, "unable to write metadata as file comment for file \"%s\" while creating zip-based phar \"%s\"", entry->filename, entry->phar->fname);
			smart_str_free(&entry->metadata_str);
			return ZEND_HASH_APPLY_STOP;
		}

		smart_str_free(&entry->metadata_str);
	}

	return ZEND_HASH_APPLY_KEEP;
}