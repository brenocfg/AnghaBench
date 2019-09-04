#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* free_chunk ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_5__ {TYPE_1__ row_buffer; TYPE_3__* result_set_memory_pool; } ;
typedef  TYPE_2__ MYSQLND_PACKET_ROW ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_VOID_RETURN ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
php_mysqlnd_rowp_free_mem(void * _packet)
{
	MYSQLND_PACKET_ROW *p;

	DBG_ENTER("php_mysqlnd_rowp_free_mem");
	p = (MYSQLND_PACKET_ROW *) _packet;
	if (p->row_buffer.ptr) {
		p->result_set_memory_pool->free_chunk(p->result_set_memory_pool, p->row_buffer.ptr);
		p->row_buffer.ptr = NULL;
	}
	/*
	  Don't free packet->fields :
	  - normal queries -> store_result() | fetch_row_unbuffered() will transfer
	    the ownership and NULL it.
	  - PS will pass in it the bound variables, we have to use them! and of course
	    not free the array. As it is passed to us, we should not clean it ourselves.
	*/
	DBG_VOID_RETURN;
}