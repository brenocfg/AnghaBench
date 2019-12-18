#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_uchar ;
struct TYPE_3__ {scalar_t__ decimals; } ;
typedef  TYPE_1__ MYSQLND_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,float) ; 
 int /*<<< orphan*/  DBG_VOID_RETURN ; 
 scalar_t__ NOT_FIXED_DEC ; 
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  float4get (float,int /*<<< orphan*/  const*) ; 
 double mysql_float_to_double (float,int) ; 

__attribute__((used)) static void
ps_fetch_float(zval * zv, const MYSQLND_FIELD * const field, const unsigned int pack_len, const zend_uchar ** row)
{
	float fval;
	double dval;
	DBG_ENTER("ps_fetch_float");
	float4get(fval, *row);
	(*row)+= 4;
	DBG_INF_FMT("value=%f", fval);

#ifndef NOT_FIXED_DEC
# define NOT_FIXED_DEC 31
#endif

	dval = mysql_float_to_double(fval, (field->decimals >= NOT_FIXED_DEC) ? -1 : (int)field->decimals);

	ZVAL_DOUBLE(zv, dval);
	DBG_VOID_RETURN;
}