#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_off_t ;
struct _phar_zip_pass {char** error; int /*<<< orphan*/  centralfp; int /*<<< orphan*/  filefp; } ;
struct TYPE_8__ {scalar_t__ s; } ;
typedef  TYPE_1__ smart_str ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_9__ {char* filename; int filename_len; int is_modified; size_t uncompressed_filesize; size_t compressed_filesize; TYPE_3__* phar; int /*<<< orphan*/ * fp; int /*<<< orphan*/  fp_type; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ phar_entry_info ;
struct TYPE_10__ {size_t sig_flags; char* fname; int /*<<< orphan*/  is_data; } ;
typedef  TYPE_3__ phar_archive_data ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  PHAR_MOD ; 
 int /*<<< orphan*/  PHAR_SET_32 (char*,size_t) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUCCESS ; 
 size_t ZSTR_LEN (scalar_t__) ; 
 char* ZSTR_VAL (scalar_t__) ; 
 size_t Z_UL (int) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int phar_create_signature (TYPE_3__*,int /*<<< orphan*/ *,char**,size_t*,char**) ; 
 int /*<<< orphan*/  phar_zip_changed_apply_int (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_copy_to_stream_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* php_stream_fopen_tmpfile () ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_tell (int /*<<< orphan*/ ) ; 
 size_t php_stream_write (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int phar_zip_applysignature(phar_archive_data *phar, struct _phar_zip_pass *pass,
				   smart_str *metadata) /* {{{ */
{
	/* add signature for executable tars or tars explicitly set with setSignatureAlgorithm */
	if (!phar->is_data || phar->sig_flags) {
		size_t signature_length;
		char *signature, sigbuf[8];
		phar_entry_info entry = {0};
		php_stream *newfile;
		zend_off_t tell;

		newfile = php_stream_fopen_tmpfile();
		if (newfile == NULL) {
			spprintf(pass->error, 0, "phar error: unable to create temporary file for the signature file");
			return FAILURE;
		}
		tell = php_stream_tell(pass->filefp);
		/* copy the local files, central directory, and the zip comment to generate the hash */
		php_stream_seek(pass->filefp, 0, SEEK_SET);
		php_stream_copy_to_stream_ex(pass->filefp, newfile, tell, NULL);
		tell = php_stream_tell(pass->centralfp);
		php_stream_seek(pass->centralfp, 0, SEEK_SET);
		php_stream_copy_to_stream_ex(pass->centralfp, newfile, tell, NULL);
		if (metadata->s) {
			php_stream_write(newfile, ZSTR_VAL(metadata->s), ZSTR_LEN(metadata->s));
		}

		if (FAILURE == phar_create_signature(phar, newfile, &signature, &signature_length, pass->error)) {
			if (pass->error) {
				char *save = *(pass->error);
				spprintf(pass->error, 0, "phar error: unable to write signature to zip-based phar: %s", save);
				efree(save);
			}

			php_stream_close(newfile);
			return FAILURE;
		}

		entry.filename = ".phar/signature.bin";
		entry.filename_len = sizeof(".phar/signature.bin")-1;
		entry.fp = php_stream_fopen_tmpfile();
		entry.fp_type = PHAR_MOD;
		entry.is_modified = 1;
		if (entry.fp == NULL) {
			spprintf(pass->error, 0, "phar error: unable to create temporary file for signature");
			return FAILURE;
		}

		PHAR_SET_32(sigbuf, phar->sig_flags);
		PHAR_SET_32(sigbuf + 4, signature_length);

		if (Z_UL(8) != php_stream_write(entry.fp, sigbuf, 8) || signature_length != php_stream_write(entry.fp, signature, signature_length)) {
			efree(signature);
			if (pass->error) {
				spprintf(pass->error, 0, "phar error: unable to write signature to zip-based phar %s", phar->fname);
			}

			php_stream_close(newfile);
			return FAILURE;
		}

		efree(signature);
		entry.uncompressed_filesize = entry.compressed_filesize = signature_length + 8;
		entry.phar = phar;
		/* throw out return value and write the signature */
		phar_zip_changed_apply_int(&entry, (void *)pass);
		php_stream_close(newfile);

		if (pass->error && *(pass->error)) {
			/* error is set by writeheaders */
			return FAILURE;
		}
	} /* signature */
	return SUCCESS;
}