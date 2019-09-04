#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  scalar_t__ enum_func_status ;
struct TYPE_22__ {int /*<<< orphan*/  (* free_chunk ) (TYPE_6__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* resize_chunk ) (TYPE_6__*,int /*<<< orphan*/ *,size_t,size_t) ;int /*<<< orphan*/ * (* get_chunk ) (TYPE_6__*,size_t) ;} ;
struct TYPE_21__ {size_t size; } ;
struct TYPE_20__ {TYPE_2__* data; } ;
struct TYPE_19__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_17__ {scalar_t__ (* receive ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_18__ {TYPE_1__ m; } ;
typedef  int /*<<< orphan*/  MYSQLND_VIO ;
typedef  int /*<<< orphan*/  MYSQLND_STATS ;
typedef  TYPE_3__ MYSQLND_ROW_BUFFER ;
typedef  TYPE_4__ MYSQLND_PFC ;
typedef  TYPE_5__ MYSQLND_PACKET_HEADER ;
typedef  TYPE_6__ MYSQLND_MEMORY_POOL ;
typedef  int /*<<< orphan*/  MYSQLND_ERROR_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAIL ; 
 size_t MYSQLND_MAX_PACKET_SIZE ; 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  SET_OOM_ERROR (int /*<<< orphan*/ *) ; 
 scalar_t__ UNEXPECTED (int) ; 
 scalar_t__ mysqlnd_read_header (TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_6__*,size_t) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (TYPE_6__*,int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ stub4 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum_func_status
php_mysqlnd_read_row_ex(MYSQLND_PFC * pfc,
						MYSQLND_VIO * vio,
						MYSQLND_STATS * stats,
						MYSQLND_ERROR_INFO * error_info,
						MYSQLND_MEMORY_POOL * pool,
						MYSQLND_ROW_BUFFER * buffer,
						size_t * const data_size)
{
	enum_func_status ret = PASS;
	MYSQLND_PACKET_HEADER header;
	zend_uchar * p = NULL;
	size_t prealloc_more_bytes;

	DBG_ENTER("php_mysqlnd_read_row_ex");

	/*
	  To ease the process the server splits everything in packets up to 2^24 - 1.
	  Even in the case the payload is evenly divisible by this value, the last
	  packet will be empty, namely 0 bytes. Thus, we can read every packet and ask
	  for next one if they have 2^24 - 1 sizes. But just read the header of a
	  zero-length byte, don't read the body, there is no such.
	*/

	/*
	  We're allocating an extra byte, as php_mysqlnd_rowp_read_text_protocol_aux
	  needs to be able to append a terminating \0 for atoi/atof.
	*/
	prealloc_more_bytes = 1;

	*data_size = 0;
	if (UNEXPECTED(FAIL == mysqlnd_read_header(pfc, vio, &header, stats, error_info))) {
		ret = FAIL;
	} else {
		*data_size += header.size;
		buffer->ptr = pool->get_chunk(pool, *data_size + prealloc_more_bytes);
		p = buffer->ptr;

		if (UNEXPECTED(PASS != (ret = pfc->data->m.receive(pfc, vio, p, header.size, stats, error_info)))) {
			DBG_ERR("Empty row packet body");
			php_error(E_WARNING, "Empty row packet body");
		} else {
			while (header.size >= MYSQLND_MAX_PACKET_SIZE) {
				if (FAIL == mysqlnd_read_header(pfc, vio, &header, stats, error_info)) {
					ret = FAIL;
					break;
				}

				*data_size += header.size;

				/* Empty packet after MYSQLND_MAX_PACKET_SIZE packet. That's ok, break */
				if (!header.size) {
					break;
				}

				/*
				  We have to realloc the buffer.
				*/
				buffer->ptr = pool->resize_chunk(pool, buffer->ptr, *data_size - header.size, *data_size + prealloc_more_bytes);
				if (!buffer->ptr) {
					SET_OOM_ERROR(error_info);
					ret = FAIL;
					break;
				}
				/* The position could have changed, recalculate */
				p = (zend_uchar *) buffer->ptr + (*data_size - header.size);

				if (PASS != (ret = pfc->data->m.receive(pfc, vio, p, header.size, stats, error_info))) {
					DBG_ERR("Empty row packet body");
					php_error(E_WARNING, "Empty row packet body");
					break;
				}
			}
		}
	}
	if (ret == FAIL && buffer->ptr) {
		pool->free_chunk(pool, buffer->ptr);
		buffer->ptr = NULL;
	}
	DBG_RETURN(ret);
}