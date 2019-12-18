#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ flatfile ;
struct TYPE_11__ {scalar_t__ dsize; int /*<<< orphan*/  dptr; } ;
typedef  TYPE_2__ datum ;

/* Variables and functions */
 int FLATFILE_INSERT ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  flatfile_delete (TYPE_1__*,TYPE_2__) ; 
 scalar_t__ flatfile_findkey (TYPE_1__*,TYPE_2__) ; 
 int /*<<< orphan*/  php_stream_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  php_stream_seek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 scalar_t__ php_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int flatfile_store(flatfile *dba, datum key_datum, datum value_datum, int mode) {
	if (mode == FLATFILE_INSERT) {
		if (flatfile_findkey(dba, key_datum)) {
			return 1;
		}
		php_stream_seek(dba->fp, 0L, SEEK_END);
		php_stream_printf(dba->fp, "%zu\n", key_datum.dsize);
		php_stream_flush(dba->fp);
		if (php_stream_write(dba->fp, key_datum.dptr, key_datum.dsize) < key_datum.dsize) {
			return -1;
		}
		php_stream_printf(dba->fp, "%zu\n", value_datum.dsize);
		php_stream_flush(dba->fp);
		if (php_stream_write(dba->fp, value_datum.dptr, value_datum.dsize) < value_datum.dsize) {
			return -1;
		}
	} else { /* FLATFILE_REPLACE */
		flatfile_delete(dba, key_datum);
		php_stream_printf(dba->fp, "%zu\n", key_datum.dsize);
		php_stream_flush(dba->fp);
		if (php_stream_write(dba->fp, key_datum.dptr, key_datum.dsize) < key_datum.dsize) {
			return -1;
		}
		php_stream_printf(dba->fp, "%zu\n", value_datum.dsize);
		if (php_stream_write(dba->fp, value_datum.dptr, value_datum.dsize) < value_datum.dsize) {
			return -1;
		}
	}

	php_stream_flush(dba->fp);
	return 0;
}