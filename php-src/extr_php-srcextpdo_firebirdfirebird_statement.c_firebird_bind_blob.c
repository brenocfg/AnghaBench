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
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_ulong ;
struct TYPE_6__ {scalar_t__ driver_data; } ;
typedef  TYPE_1__ pdo_stmt_t ;
struct TYPE_7__ {TYPE_3__* H; } ;
typedef  TYPE_2__ pdo_firebird_stmt ;
struct TYPE_8__ {int /*<<< orphan*/  isc_status; int /*<<< orphan*/  tr; int /*<<< orphan*/  db; } ;
typedef  TYPE_3__ pdo_firebird_db_handle ;
typedef  int /*<<< orphan*/  isc_blob_handle ;
typedef  int /*<<< orphan*/  ISC_QUAD ;

/* Variables and functions */
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  PDO_FIREBIRD_HANDLE_INITIALIZER ; 
 int /*<<< orphan*/  RECORD_ERROR (TYPE_1__*) ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  ZVAL_COPY_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Z_STRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ isc_close_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ isc_create_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isc_put_segment (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_get_string_func (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int firebird_bind_blob(pdo_stmt_t *stmt, ISC_QUAD *blob_id, zval *param)
{
	pdo_firebird_stmt *S = (pdo_firebird_stmt*)stmt->driver_data;
	pdo_firebird_db_handle *H = S->H;
	isc_blob_handle h = PDO_FIREBIRD_HANDLE_INITIALIZER;
	zval data;
	zend_ulong put_cnt = 0, rem_cnt;
	unsigned short chunk_size;
	int result = 1;

	if (isc_create_blob(H->isc_status, &H->db, &H->tr, &h, blob_id)) {
		RECORD_ERROR(stmt);
		return 0;
	}

	if (Z_TYPE_P(param) != IS_STRING) {
		ZVAL_STR(&data, zval_get_string_func(param));
	} else {
		ZVAL_COPY_VALUE(&data, param);
	}

	for (rem_cnt = Z_STRLEN(data); rem_cnt > 0; rem_cnt -= chunk_size) {
		chunk_size = rem_cnt > USHRT_MAX ? USHRT_MAX : (unsigned short)rem_cnt;
		if (isc_put_segment(H->isc_status, &h, chunk_size, &Z_STRVAL(data)[put_cnt])) {
			RECORD_ERROR(stmt);
			result = 0;
			break;
		}
		put_cnt += chunk_size;
	}

	if (Z_TYPE_P(param) != IS_STRING) {
		zval_ptr_dtor_str(&data);
	}

	if (isc_close_blob(H->isc_status, &h)) {
		RECORD_ERROR(stmt);
		return 0;
	}
	return result;
}