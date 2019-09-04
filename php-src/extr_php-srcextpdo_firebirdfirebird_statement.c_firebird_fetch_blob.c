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
typedef  scalar_t__ zend_ulong ;
struct TYPE_6__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_7__ {char** fetch_buf; TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_firebird_stmt ;
struct TYPE_8__ {int* isc_status; char* last_app_error; int /*<<< orphan*/  tr; int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ pdo_firebird_db_handle ;
typedef  int /*<<< orphan*/  isc_blob_handle ;
typedef  int /*<<< orphan*/  bl_info ;
typedef  scalar_t__ ISC_STATUS ;
typedef  int /*<<< orphan*/  ISC_QUAD ;

/* Variables and functions */
 int /*<<< orphan*/  PDO_FIREBIRD_HANDLE_INITIALIZER ; 
 int /*<<< orphan*/  RECORD_ERROR (TYPE_1__*) ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  const_cast (char const*) ; 
 char* erealloc (char*,scalar_t__) ; 
 scalar_t__ isc_blob_info (int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ isc_close_blob (int*,int /*<<< orphan*/ *) ; 
 scalar_t__ isc_get_segment (int*,int /*<<< orphan*/ *,unsigned short*,unsigned short,char*) ; 
 char isc_info_blob_total_length ; 
 char isc_info_end ; 
 char isc_info_error ; 
 char isc_info_truncated ; 
 scalar_t__ isc_open_blob (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isc_segment ; 
 scalar_t__ isc_segstr_eof ; 
 scalar_t__ isc_vax_integer (char*,unsigned short) ; 

__attribute__((used)) static int firebird_fetch_blob(pdo_stmt_t *stmt, int colno, char **ptr, /* {{{ */
	zend_ulong *len, ISC_QUAD *blob_id)
{
	pdo_firebird_stmt *S = (pdo_firebird_stmt*)stmt->driver_data;
	pdo_firebird_db_handle *H = S->H;
	isc_blob_handle blobh = PDO_FIREBIRD_HANDLE_INITIALIZER;
	char const bl_item = isc_info_blob_total_length;
	char bl_info[20];
	unsigned short i;
	int result = *len = 0;

	if (isc_open_blob(H->isc_status, &H->db, &H->tr, &blobh, blob_id)) {
		RECORD_ERROR(stmt);
		return 0;
	}

	if (isc_blob_info(H->isc_status, &blobh, 1, const_cast(&bl_item),
			sizeof(bl_info), bl_info)) {
		RECORD_ERROR(stmt);
		goto fetch_blob_end;
	}

	/* find total length of blob's data */
	for (i = 0; i < sizeof(bl_info); ) {
		unsigned short item_len;
		char item = bl_info[i++];

		if (item == isc_info_end || item == isc_info_truncated || item == isc_info_error
				|| i >= sizeof(bl_info)) {
			H->last_app_error = "Couldn't determine BLOB size";
			goto fetch_blob_end;
		}

		item_len = (unsigned short) isc_vax_integer(&bl_info[i], 2);

		if (item == isc_info_blob_total_length) {
			*len = isc_vax_integer(&bl_info[i+2], item_len);
			break;
		}
		i += item_len+2;
	}

	/* we've found the blob's length, now fetch! */

	if (*len) {
		zend_ulong cur_len;
		unsigned short seg_len;
		ISC_STATUS stat;

		*ptr = S->fetch_buf[colno] = erealloc(S->fetch_buf[colno], *len+1);

		for (cur_len = stat = 0; (!stat || stat == isc_segment) && cur_len < *len; cur_len += seg_len) {

			unsigned short chunk_size = (*len-cur_len) > USHRT_MAX ? USHRT_MAX
				: (unsigned short)(*len-cur_len);

			stat = isc_get_segment(H->isc_status, &blobh, &seg_len, chunk_size, &(*ptr)[cur_len]);
		}

		(*ptr)[*len++] = '\0';

		if (H->isc_status[0] == 1 && (stat != 0 && stat != isc_segstr_eof && stat != isc_segment)) {
			H->last_app_error = "Error reading from BLOB";
			goto fetch_blob_end;
		}
	}
	result = 1;

fetch_blob_end:
	if (isc_close_blob(H->isc_status, &blobh)) {
		RECORD_ERROR(stmt);
		return 0;
	}
	return result;
}