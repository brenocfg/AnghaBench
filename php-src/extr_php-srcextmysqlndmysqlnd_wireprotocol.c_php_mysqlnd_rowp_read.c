#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  scalar_t__ zend_uchar ;
typedef  scalar_t__ enum_func_status ;
struct TYPE_11__ {size_t size; scalar_t__* ptr; } ;
struct TYPE_10__ {int /*<<< orphan*/ * stats; int /*<<< orphan*/ * vio; int /*<<< orphan*/ * protocol_frame_codec; int /*<<< orphan*/ * error_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  sqlstate; int /*<<< orphan*/  error_no; int /*<<< orphan*/  error; } ;
struct TYPE_7__ {size_t size; } ;
struct TYPE_9__ {scalar_t__ binary_protocol; int /*<<< orphan*/  field_count; scalar_t__ fields; int /*<<< orphan*/  skip_extraction; int /*<<< orphan*/  eof; void* warning_count; void* server_status; TYPE_2__ error_info; TYPE_6__ row_buffer; TYPE_1__ header; int /*<<< orphan*/  result_set_memory_pool; } ;
typedef  int /*<<< orphan*/  MYSQLND_VIO ;
typedef  int /*<<< orphan*/  MYSQLND_STATS ;
typedef  int /*<<< orphan*/  MYSQLND_PFC ;
typedef  TYPE_3__ MYSQLND_PACKET_ROW ;
typedef  int /*<<< orphan*/  MYSQLND_ERROR_INFO ;
typedef  TYPE_4__ MYSQLND_CONN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,void*,void*) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ EODATA_MARKER ; 
 scalar_t__ ERROR_MARKER ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MYSQLND_HEADER_SIZE ; 
 int /*<<< orphan*/  MYSQLND_INC_CONN_STATISTIC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MYSQLND_INC_CONN_STATISTIC_W_VALUE2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PASS ; 
 size_t PROT_ROW_PACKET ; 
 int /*<<< orphan*/  STAT_ROWS_FETCHED_FROM_SERVER_NORMAL ; 
 int /*<<< orphan*/  STAT_ROWS_FETCHED_FROM_SERVER_PS ; 
 int /*<<< orphan*/  STAT_ROWS_SKIPPED_NORMAL ; 
 int /*<<< orphan*/  STAT_ROWS_SKIPPED_PS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ mnd_ecalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * packet_type_to_statistic_byte_count ; 
 int /*<<< orphan*/ * packet_type_to_statistic_packet_count ; 
 int /*<<< orphan*/  php_mysqlnd_read_error_from_line (scalar_t__*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ php_mysqlnd_read_row_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*,size_t*) ; 
 void* uint2korr (scalar_t__*) ; 

__attribute__((used)) static enum_func_status
php_mysqlnd_rowp_read(MYSQLND_CONN_DATA * conn, void * _packet)
{
	MYSQLND_PACKET_ROW *packet= (MYSQLND_PACKET_ROW *) _packet;
	MYSQLND_ERROR_INFO * error_info = conn->error_info;
	MYSQLND_PFC * pfc = conn->protocol_frame_codec;
	MYSQLND_VIO * vio = conn->vio;
	MYSQLND_STATS * stats = conn->stats;
	zend_uchar *p;
	enum_func_status ret = PASS;
	size_t data_size = 0;

	DBG_ENTER("php_mysqlnd_rowp_read");

	ret = php_mysqlnd_read_row_ex(pfc, vio, stats, error_info,
								  packet->result_set_memory_pool, &packet->row_buffer, &data_size);
	if (FAIL == ret) {
		goto end;
	}
	MYSQLND_INC_CONN_STATISTIC_W_VALUE2(stats, packet_type_to_statistic_byte_count[PROT_ROW_PACKET],
										MYSQLND_HEADER_SIZE + packet->header.size,
										packet_type_to_statistic_packet_count[PROT_ROW_PACKET],
										1);

	/*
	  packet->row_buffer->ptr is of size 'data_size'
	  in pre-7.0 it was really 'data_size + 1' although it was counted as 'data_size'
	  The +1 was for the additional byte needed to \0 terminate the last string in the row.
	  This was needed as the zvals of pre-7.0 could use external memory (no copy param to ZVAL_STRINGL).
	  However, in 7.0+ the strings always copy. Thus this +1 byte was removed. Also the optimization or \0
	  terminating every string, which did overwrite the lengths from the packet. For this reason we needed
	  to keep (and copy) the lengths externally.
	*/
	packet->header.size = data_size;
	packet->row_buffer.size = data_size;

	if (ERROR_MARKER == (*(p = packet->row_buffer.ptr))) {
		/*
		   Error message as part of the result set,
		   not good but we should not hang. See:
		   Bug #27876 : SF with cyrillic variable name fails during execution
		*/
		ret = FAIL;
		php_mysqlnd_read_error_from_line(p + 1, data_size - 1,
										 packet->error_info.error,
										 sizeof(packet->error_info.error),
										 &packet->error_info.error_no,
										 packet->error_info.sqlstate
										);
	} else if (EODATA_MARKER == *p && data_size < 8) { /* EOF */
		packet->eof = TRUE;
		p++;
		if (data_size > 1) {
			packet->warning_count = uint2korr(p);
			p += 2;
			packet->server_status = uint2korr(p);
			/* Seems we have 3 bytes reserved for future use */
			DBG_INF_FMT("server_status=%u warning_count=%u", packet->server_status, packet->warning_count);
		}
	} else {
		MYSQLND_INC_CONN_STATISTIC(stats,
									packet->binary_protocol? STAT_ROWS_FETCHED_FROM_SERVER_PS:
															 STAT_ROWS_FETCHED_FROM_SERVER_NORMAL);

		packet->eof = FALSE;
		/* packet->field_count is set by the user of the packet */

		if (!packet->skip_extraction) {
			if (!packet->fields) {
				DBG_INF("Allocating packet->fields");
				/*
				  old-API will probably set packet->fields to NULL every time, though for
				  unbuffered sets it makes not much sense as the zvals in this buffer matter,
				  not the buffer. Constantly allocating and deallocating brings nothing.

				  For PS - if stmt_store() is performed, thus we don't have a cursor, it will
				  behave just like old-API buffered. Cursors will behave like a bit different,
				  but mostly like old-API unbuffered and thus will populate this array with
				  value.
				*/
				packet->fields = mnd_ecalloc(packet->field_count, sizeof(zval));
			}
		} else {
			MYSQLND_INC_CONN_STATISTIC(stats,
										packet->binary_protocol? STAT_ROWS_SKIPPED_PS:
																 STAT_ROWS_SKIPPED_NORMAL);
		}
	}

end:
	DBG_RETURN(ret);
}