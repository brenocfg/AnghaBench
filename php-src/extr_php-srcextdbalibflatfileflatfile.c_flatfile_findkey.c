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
struct TYPE_6__ {size_t dsize; void* dptr; } ;
typedef  TYPE_2__ datum ;

/* Variables and functions */
 size_t FLATFILE_BLOCK_SIZE ; 
 size_t atoi (char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 char* erealloc (char*,size_t) ; 
 int /*<<< orphan*/  memcmp (char*,void*,size_t) ; 
 int /*<<< orphan*/  php_stream_eof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_gets (int /*<<< orphan*/ ,char*,int) ; 
 size_t php_stream_read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  php_stream_rewind (int /*<<< orphan*/ ) ; 

int flatfile_findkey(flatfile *dba, datum key_datum) {
	size_t buf_size = FLATFILE_BLOCK_SIZE;
	char *buf = emalloc(buf_size);
	size_t num;
	int ret=0;
	void *key = key_datum.dptr;
	size_t size = key_datum.dsize;

	php_stream_rewind(dba->fp);
	while (!php_stream_eof(dba->fp)) {
		if (!php_stream_gets(dba->fp, buf, 15)) {
			break;
		}
		num = atoi(buf);
		if (num >= buf_size) {
			buf_size = num + FLATFILE_BLOCK_SIZE;
			buf = erealloc(buf, buf_size);
		}
		num = php_stream_read(dba->fp, buf, num);

		if (size == num) {
			if (!memcmp(buf, key, size)) {
				ret = 1;
				break;
			}
		}
		if (!php_stream_gets(dba->fp, buf, 15)) {
			break;
		}
		num = atoi(buf);
		if (num >= buf_size) {
			buf_size = num + FLATFILE_BLOCK_SIZE;
			buf = erealloc(buf, buf_size);
		}
		num = php_stream_read(dba->fp, buf, num);
	}
	efree(buf);
	return ret;
}