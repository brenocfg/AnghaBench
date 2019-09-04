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
struct TYPE_5__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ flatfile ;
struct TYPE_6__ {char* dptr; size_t dsize; } ;
typedef  TYPE_2__ datum ;

/* Variables and functions */
 int FAILURE ; 
 size_t FLATFILE_BLOCK_SIZE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUCCESS ; 
 size_t atoi (char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 char* erealloc (char*,size_t) ; 
 int /*<<< orphan*/  memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  php_stream_eof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_gets (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  php_stream_putc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t php_stream_read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  php_stream_rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 size_t php_stream_tell (int /*<<< orphan*/ ) ; 

int flatfile_delete(flatfile *dba, datum key_datum) {
	char *key = key_datum.dptr;
	size_t size = key_datum.dsize;
	size_t buf_size = FLATFILE_BLOCK_SIZE;
	char *buf = emalloc(buf_size);
	size_t num;
	size_t pos;

	php_stream_rewind(dba->fp);
	while(!php_stream_eof(dba->fp)) {
		/* read in the length of the key name */
		if (!php_stream_gets(dba->fp, buf, 15)) {
			break;
		}
		num = atoi(buf);
		if (num >= buf_size) {
			buf_size = num + FLATFILE_BLOCK_SIZE;
			buf = erealloc(buf, buf_size);
		}
		pos = php_stream_tell(dba->fp);

		/* read in the key name */
		num = php_stream_read(dba->fp, buf, num);

		if (size == num && !memcmp(buf, key, size)) {
			php_stream_seek(dba->fp, pos, SEEK_SET);
			php_stream_putc(dba->fp, 0);
			php_stream_flush(dba->fp);
			php_stream_seek(dba->fp, 0L, SEEK_END);
			efree(buf);
			return SUCCESS;
		}

		/* read in the length of the value */
		if (!php_stream_gets(dba->fp, buf, 15)) {
			break;
		}
		num = atoi(buf);
		if (num >= buf_size) {
			buf_size = num + FLATFILE_BLOCK_SIZE;
			buf = erealloc(buf, buf_size);
		}
		/* read in the value */
		num = php_stream_read(dba->fp, buf, num);
	}
	efree(buf);
	return FAILURE;
}