#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  scalar_t__ enum_func_status ;
struct TYPE_10__ {TYPE_1__* data; } ;
struct TYPE_9__ {int param_count; int send_types_to_server; int /*<<< orphan*/  error_info; } ;
typedef  TYPE_1__ MYSQLND_STMT_DATA ;
typedef  TYPE_2__ MYSQLND_STMT ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,char*) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ FAIL ; 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  SET_OOM_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int1store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ mysqlnd_stmt_execute_calculate_param_values_size (TYPE_1__*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ mysqlnd_stmt_execute_check_n_enlarge_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ mysqlnd_stmt_execute_prepare_param_types (TYPE_1__*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  mysqlnd_stmt_execute_store_param_values (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t) ; 
 int /*<<< orphan*/  mysqlnd_stmt_execute_store_types (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mysqlnd_stmt_free_copies (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum_func_status
mysqlnd_stmt_execute_store_params(MYSQLND_STMT * s, zend_uchar **buf, zend_uchar **p, size_t *buf_len )
{
	MYSQLND_STMT_DATA * stmt = s->data;
	zend_uchar * provided_buffer = *buf;
	size_t data_size = 0;
	zval *copies = NULL;/* if there are different types */
	enum_func_status ret = FAIL;
	int resend_types_next_time = 0;
	size_t null_byte_offset;

	DBG_ENTER("mysqlnd_stmt_execute_store_params");

	{
		unsigned int null_count = (stmt->param_count + 7) / 8;
		if (FAIL == mysqlnd_stmt_execute_check_n_enlarge_buffer(buf, p, buf_len, provided_buffer, null_count)) {
			SET_OOM_ERROR(stmt->error_info);
			goto end;
		}
		/* put `null` bytes */
		null_byte_offset = *p - *buf;
		memset(*p, 0, null_count);
		*p += null_count;
	}

/* 1. Store type information */
	/*
	  check if need to send the types even if stmt->send_types_to_server is 0. This is because
	  if we send "i" (42) then the type will be int and the server will expect int. However, if next
	  time we try to send > LONG_MAX, the conversion to string will send a string and the server
	  won't expect it and interpret the value as 0. Thus we need to resend the types, if any such values
	  occur, and force resend for the next execution.
	*/
	if (FAIL == mysqlnd_stmt_execute_prepare_param_types(stmt, &copies, &resend_types_next_time)) {
		goto end;
	}

	int1store(*p, stmt->send_types_to_server);
	(*p)++;

	if (stmt->send_types_to_server) {
		if (FAIL == mysqlnd_stmt_execute_check_n_enlarge_buffer(buf, p, buf_len, provided_buffer, stmt->param_count * 2)) {
			SET_OOM_ERROR(stmt->error_info);
			goto end;
		}
		mysqlnd_stmt_execute_store_types(stmt, copies, p);
	}

	stmt->send_types_to_server = resend_types_next_time;

/* 2. Store data */
	/* 2.1 Calculate how much space we need */
	if (FAIL == mysqlnd_stmt_execute_calculate_param_values_size(stmt, &copies, &data_size)) {
		goto end;
	}

	/* 2.2 Enlarge the buffer, if needed */
	if (FAIL == mysqlnd_stmt_execute_check_n_enlarge_buffer(buf, p, buf_len, provided_buffer, data_size)) {
		SET_OOM_ERROR(stmt->error_info);
		goto end;
	}

	/* 2.3 Store the actual data */
	mysqlnd_stmt_execute_store_param_values(stmt, copies, *buf, p, null_byte_offset);

	ret = PASS;
end:
	mysqlnd_stmt_free_copies(stmt, copies);

	DBG_INF_FMT("ret=%s", ret == PASS? "PASS":"FAIL");
	DBG_RETURN(ret);
}