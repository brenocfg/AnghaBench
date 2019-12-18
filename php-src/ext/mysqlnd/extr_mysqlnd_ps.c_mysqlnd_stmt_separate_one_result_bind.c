#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ bound; int /*<<< orphan*/  zv; } ;
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {TYPE_4__* result_bind; int /*<<< orphan*/  field_count; int /*<<< orphan*/  stmt_id; } ;
typedef  TYPE_1__ MYSQLND_STMT_DATA ;
typedef  TYPE_2__ MYSQLND_STMT ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,unsigned int const,TYPE_4__*,...) ; 
 int /*<<< orphan*/  DBG_VOID_RETURN ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  Z_REFCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_REFCOUNTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mysqlnd_stmt_separate_one_result_bind(MYSQLND_STMT * const s, const unsigned int param_no)
{
	MYSQLND_STMT_DATA * stmt = s? s->data : NULL;
	DBG_ENTER("mysqlnd_stmt_separate_one_result_bind");
	if (!stmt) {
		DBG_VOID_RETURN;
	}
	DBG_INF_FMT("stmt=%lu result_bind=%p field_count=%u param_no=%u", stmt->stmt_id, stmt->result_bind, stmt->field_count, param_no);

	if (!stmt->result_bind) {
		DBG_VOID_RETURN;
	}

	/*
	  Because only the bound variables can point to our internal buffers, then
	  separate or free only them. Free is possible because the user could have
	  lost reference.
	*/
	/* Let's try with no cache */
	if (stmt->result_bind[param_no].bound == TRUE) {
		DBG_INF_FMT("%u has refcount=%u", param_no, Z_REFCOUNTED(stmt->result_bind[param_no].zv)? Z_REFCOUNT(stmt->result_bind[param_no].zv) : 0);
		zval_ptr_dtor(&stmt->result_bind[param_no].zv);
	}

	DBG_VOID_RETURN;
}