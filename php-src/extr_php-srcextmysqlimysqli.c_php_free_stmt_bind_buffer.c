#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* val; } ;
struct TYPE_5__ {unsigned int var_cnt; TYPE_2__* is_null; TYPE_2__* buf; TYPE_2__* vars; } ;
typedef  TYPE_1__ BIND_BUFFER ;

/* Variables and functions */
 int FETCH_RESULT ; 
 int FETCH_SIMPLE ; 
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (TYPE_2__*) ; 

void php_free_stmt_bind_buffer(BIND_BUFFER bbuf, int type)
{
	unsigned int i;

	if (!bbuf.var_cnt) {
		return;
	}

	for (i=0; i < bbuf.var_cnt; i++) {

		/* free temporary bind buffer */
		if (type == FETCH_RESULT && bbuf.buf[i].val) {
			efree(bbuf.buf[i].val);
		}

		zval_ptr_dtor(&bbuf.vars[i]);
	}

	if (bbuf.vars) {
		efree(bbuf.vars);
	}

	/*
	  Don't free bbuf.is_null for FETCH_RESULT since we have allocated
	  is_null and buf in one block so we free only buf, which is the beginning
	  of the block. When FETCH_SIMPLE then buf wasn't allocated together with
	  buf and we have to free it.
	*/
	if (type == FETCH_RESULT) {
		efree(bbuf.buf);
	} else if (type == FETCH_SIMPLE){
		efree(bbuf.is_null);
	}

	bbuf.var_cnt = 0;
}