#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ flatfile ;
struct TYPE_9__ {scalar_t__ dsize; int /*<<< orphan*/ * dptr; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ datum ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ atoi (char*) ; 
 scalar_t__ flatfile_findkey (TYPE_1__*,TYPE_2__) ; 
 scalar_t__ php_stream_gets (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ php_stream_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * safe_emalloc (scalar_t__,int,int) ; 

datum flatfile_fetch(flatfile *dba, datum key_datum) {
	datum value_datum = {NULL, 0};
	char buf[16];

	if (flatfile_findkey(dba, key_datum)) {
		if (php_stream_gets(dba->fp, buf, sizeof(buf))) {
			value_datum.dsize = atoi(buf);
			value_datum.dptr = safe_emalloc(value_datum.dsize, 1, 1);
			value_datum.dsize = php_stream_read(dba->fp, value_datum.dptr, value_datum.dsize);
		} else {
			value_datum.dptr = NULL;
			value_datum.dsize = 0;
		}
	}
	return value_datum;
}