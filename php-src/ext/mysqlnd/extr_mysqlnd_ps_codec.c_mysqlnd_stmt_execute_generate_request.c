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
typedef  int zend_uchar ;
typedef  int zend_bool ;
typedef  scalar_t__ enum_func_status ;
struct TYPE_8__ {TYPE_2__* data; } ;
struct TYPE_6__ {int* buffer; size_t length; } ;
struct TYPE_7__ {scalar_t__ param_count; TYPE_1__ execute_cmd_buffer; scalar_t__ flags; int /*<<< orphan*/  stmt_id; } ;
typedef  TYPE_2__ MYSQLND_STMT_DATA ;
typedef  TYPE_3__ MYSQLND_STMT ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,char*) ; 
 int /*<<< orphan*/  DBG_RETURN (scalar_t__) ; 
 scalar_t__ PASS ; 
 int /*<<< orphan*/  int1store (int*,int) ; 
 int /*<<< orphan*/  int4store (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ mysqlnd_stmt_execute_store_params (TYPE_3__* const,int**,int**,size_t*) ; 

enum_func_status
mysqlnd_stmt_execute_generate_request(MYSQLND_STMT * const s, zend_uchar ** request, size_t *request_len, zend_bool * free_buffer)
{
	MYSQLND_STMT_DATA * stmt = s->data;
	zend_uchar	*p = stmt->execute_cmd_buffer.buffer,
				*cmd_buffer = stmt->execute_cmd_buffer.buffer;
	size_t cmd_buffer_length = stmt->execute_cmd_buffer.length;
	enum_func_status ret = PASS;

	DBG_ENTER("mysqlnd_stmt_execute_generate_request");

	int4store(p, stmt->stmt_id);
	p += 4;

	/* flags is 4 bytes, we store just 1 */
	int1store(p, (zend_uchar) stmt->flags);
	p++;

	/* Make it all zero */
	int4store(p, 0);

	int1store(p, 1); /* and send 1 for iteration count */
	p+= 4;

	if (stmt->param_count != 0) {
	    ret = mysqlnd_stmt_execute_store_params(s, &cmd_buffer, &p, &cmd_buffer_length);
	}

	*free_buffer = (cmd_buffer != stmt->execute_cmd_buffer.buffer);
	*request_len = (p - cmd_buffer);
	*request = cmd_buffer;
	DBG_INF_FMT("ret=%s", ret == PASS? "PASS":"FAIL");
	DBG_RETURN(ret);
}