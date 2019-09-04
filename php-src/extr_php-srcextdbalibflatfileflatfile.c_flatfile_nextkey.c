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
struct TYPE_5__ {int /*<<< orphan*/  fp; int /*<<< orphan*/  CurrentFlatFilePos; } ;
typedef  TYPE_1__ flatfile ;
struct TYPE_6__ {char* dptr; size_t dsize; } ;
typedef  TYPE_2__ datum ;

/* Variables and functions */
 size_t FLATFILE_BLOCK_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 size_t atoi (char*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 char* erealloc (char*,size_t) ; 
 int /*<<< orphan*/  php_stream_eof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_gets (int /*<<< orphan*/ ,char*,int) ; 
 size_t php_stream_read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_tell (int /*<<< orphan*/ ) ; 

datum flatfile_nextkey(flatfile *dba) {
	datum res;
	size_t num;
	size_t buf_size = FLATFILE_BLOCK_SIZE;
	char *buf = emalloc(buf_size);

	php_stream_seek(dba->fp, dba->CurrentFlatFilePos, SEEK_SET);
	while(!php_stream_eof(dba->fp)) {
		if (!php_stream_gets(dba->fp, buf, 15)) {
			break;
		}
		num = atoi(buf);
		if (num >= buf_size) {
			buf_size = num + FLATFILE_BLOCK_SIZE;
			buf = erealloc(buf, buf_size);
		}
		num = php_stream_read(dba->fp, buf, num);

		if (!php_stream_gets(dba->fp, buf, 15)) {
			break;
		}
		num = atoi(buf);
		if (num >= buf_size) {
			buf_size = num + FLATFILE_BLOCK_SIZE;
			buf = erealloc(buf, buf_size);
		}
		num = php_stream_read(dba->fp, buf, num);

		if (*(buf)!=0) {
			dba->CurrentFlatFilePos = php_stream_tell(dba->fp);
			res.dptr = buf;
			res.dsize = num;
			return res;
		}
	}
	efree(buf);
	res.dptr = NULL;
	res.dsize = 0;
	return res;
}