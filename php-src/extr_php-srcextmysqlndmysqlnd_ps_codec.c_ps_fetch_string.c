#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_ulong ;
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  int /*<<< orphan*/  MYSQLND_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DBG_VOID_RETURN ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  php_mysqlnd_net_field_length (int /*<<< orphan*/  const**) ; 

__attribute__((used)) static void
ps_fetch_string(zval * zv, const MYSQLND_FIELD * const field, const unsigned int pack_len, const zend_uchar ** row)
{
	/*
	  For now just copy, before we make it possible
	  to write \0 to the row buffer
	*/
	const zend_ulong length = php_mysqlnd_net_field_length(row);
	DBG_ENTER("ps_fetch_string");
	DBG_INF_FMT("len = %lu", length);
	DBG_INF("copying from the row buffer");
	ZVAL_STRINGL(zv, (char *)*row, length);

	(*row) += length;
	DBG_VOID_RETURN;
}