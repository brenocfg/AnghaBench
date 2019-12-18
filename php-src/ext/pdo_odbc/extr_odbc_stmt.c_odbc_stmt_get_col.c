#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int zend_ulong ;
struct TYPE_6__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_7__ {char* convbuf; int /*<<< orphan*/  stmt; TYPE_3__* cols; } ;
typedef  TYPE_2__ pdo_odbc_stmt ;
struct TYPE_8__ {char* data; int fetched_len; scalar_t__ is_unicode; scalar_t__ is_long; } ;
typedef  TYPE_3__ pdo_odbc_column ;
typedef  scalar_t__ RETCODE ;

/* Variables and functions */
#define  PDO_ODBC_CONV_FAIL 130 
#define  PDO_ODBC_CONV_NOT_REQUIRED 129 
#define  PDO_ODBC_CONV_OK 128 
 scalar_t__ SQLGetData (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  SQL_C_BINARY ; 
 int /*<<< orphan*/  SQL_C_CHAR ; 
 scalar_t__ SQL_NULL_DATA ; 
 scalar_t__ SQL_SUCCESS ; 
 scalar_t__ SQL_SUCCESS_WITH_INFO ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (int) ; 
 char* erealloc (char*,int) ; 
 char* estrndup (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int pdo_odbc_ucs22utf8 (TYPE_1__*,scalar_t__,char*,int,int*) ; 

__attribute__((used)) static int odbc_stmt_get_col(pdo_stmt_t *stmt, int colno, char **ptr, zend_ulong *len, int *caller_frees)
{
	pdo_odbc_stmt *S = (pdo_odbc_stmt*)stmt->driver_data;
	pdo_odbc_column *C = &S->cols[colno];
	zend_ulong ulen;

	/* if it is a column containing "long" data, perform late binding now */
	if (C->is_long) {
		zend_ulong used = 0;
		char *buf;
		RETCODE rc;

		/* fetch it into C->data, which is allocated with a length
		 * of 256 bytes; if there is more to be had, we then allocate
		 * bigger buffer for the caller to free */

		rc = SQLGetData(S->stmt, colno+1, C->is_unicode ? SQL_C_BINARY : SQL_C_CHAR, C->data,
 			256, &C->fetched_len);

		if (rc == SQL_SUCCESS) {
			/* all the data fit into our little buffer;
			 * jump down to the generic bound data case */
			goto in_data;
		}

		if (rc == SQL_SUCCESS_WITH_INFO) {
			/* this is a 'long column'

			 read the column in 255 byte blocks until the end of the column is reached, reassembling those blocks
			 in order into the output buffer

			 this loop has to work whether or not SQLGetData() provides the total column length.
			 calling SQLDescribeCol() or other, specifically to get the column length, then doing a single read
			 for that size would be slower except maybe for extremely long columns.*/
			char *buf2;

			buf2 = emalloc(256);
			buf = estrndup(C->data, 256);
			used = 255; /* not 256; the driver NUL terminated the buffer */

			do {
				C->fetched_len = 0;
				/* read block. 256 bytes => 255 bytes are actually read, the last 1 is NULL */
				rc = SQLGetData(S->stmt, colno+1, SQL_C_CHAR, buf2, 256, &C->fetched_len);

				/* resize output buffer and reassemble block */
				if (rc==SQL_SUCCESS_WITH_INFO) {
					/* point 5, in section "Retrieving Data with SQLGetData" in http://msdn.microsoft.com/en-us/library/windows/desktop/ms715441(v=vs.85).aspx
					 states that if SQL_SUCCESS_WITH_INFO, fetched_len will be > 255 (greater than buf2's size)
					 (if a driver fails to follow that and wrote less than 255 bytes to buf2, this will AV or read garbage into buf) */
					buf = erealloc(buf, used + 255+1);
					memcpy(buf + used, buf2, 255);
					used = used + 255;
				} else if (rc==SQL_SUCCESS) {
					buf = erealloc(buf, used + C->fetched_len+1);
					memcpy(buf + used, buf2, C->fetched_len);
					used = used + C->fetched_len;
				} else {
					/* includes SQL_NO_DATA */
					break;
				}

			} while (1);

			efree(buf2);

			/* NULL terminate the buffer once, when finished, for use with the rest of PHP */
			buf[used] = '\0';

			*ptr = buf;
			*caller_frees = 1;
			*len = used;
			if (C->is_unicode) {
				goto unicode_conv;
			}
			return 1;
		}

		/* something went caca */
		*ptr = NULL;
		*len = 0;
		return 1;
	}

in_data:
	/* check the indicator to ensure that the data is intact */
	if (C->fetched_len == SQL_NULL_DATA) {
		/* A NULL value */
		*ptr = NULL;
		*len = 0;
		return 1;
	} else if (C->fetched_len >= 0) {
		/* it was stored perfectly */
		*ptr = C->data;
		*len = C->fetched_len;
		if (C->is_unicode) {
			goto unicode_conv;
		}
		return 1;
	} else {
		/* no data? */
		*ptr = NULL;
		*len = 0;
		return 1;
	}

	unicode_conv:
	switch (pdo_odbc_ucs22utf8(stmt, C->is_unicode, *ptr, *len, &ulen)) {
		case PDO_ODBC_CONV_FAIL:
			/* oh well.  They can have the binary version of it */
		case PDO_ODBC_CONV_NOT_REQUIRED:
			/* shouldn't happen... */
			return 1;

		case PDO_ODBC_CONV_OK:
			if (*caller_frees) {
				efree(*ptr);
			}
			*ptr = emalloc(ulen + 1);
			*len = ulen;
			memcpy(*ptr, S->convbuf, ulen+1);
			*caller_frees = 1;
			return 1;
	}
	return 1;
}