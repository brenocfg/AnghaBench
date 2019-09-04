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
typedef  int /*<<< orphan*/  zend_long ;
typedef  int zend_bool ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ type; int flags; } ;
typedef  TYPE_1__ MYSQLND_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,char*,...) ; 
 int /*<<< orphan*/  DBG_VOID_RETURN ; 
 scalar_t__ L64 (int) ; 
 char* MYSQLND_LLU_SPEC ; 
 scalar_t__ MYSQL_TYPE_BIT ; 
 int UNSIGNED_FLAG ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  bit_uint2korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bit_uint3korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bit_uint4korr (int /*<<< orphan*/  const*) ; 
 scalar_t__ bit_uint5korr (int /*<<< orphan*/  const*) ; 
 scalar_t__ bit_uint6korr (int /*<<< orphan*/  const*) ; 
 scalar_t__ bit_uint7korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bit_uint8korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sint2korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sint3korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sint4korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sint8korr (int /*<<< orphan*/  const*) ; 
 size_t sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  uint1korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  uint2korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  uint3korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  uint4korr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  uint8korr (int /*<<< orphan*/  const*) ; 

void
ps_fetch_from_1_to_8_bytes(zval * zv, const MYSQLND_FIELD * const field, const unsigned int pack_len,
						   const zend_uchar ** row, unsigned int byte_count)
{
	char tmp[22];
	size_t tmp_len = 0;
	zend_bool is_bit = field->type == MYSQL_TYPE_BIT;
	DBG_ENTER("ps_fetch_from_1_to_8_bytes");
	DBG_INF_FMT("zv=%p byte_count=%u", zv, byte_count);
	if (field->flags & UNSIGNED_FLAG) {
		uint64_t uval = 0;

		switch (byte_count) {
			case 8:uval = is_bit? (uint64_t) bit_uint8korr(*row):(uint64_t) uint8korr(*row);break;
			case 7:uval = bit_uint7korr(*row);break;
			case 6:uval = bit_uint6korr(*row);break;
			case 5:uval = bit_uint5korr(*row);break;
			case 4:uval = is_bit? (uint64_t) bit_uint4korr(*row):(uint64_t) uint4korr(*row);break;
			case 3:uval = is_bit? (uint64_t) bit_uint3korr(*row):(uint64_t) uint3korr(*row);break;
			case 2:uval = is_bit? (uint64_t) bit_uint2korr(*row):(uint64_t) uint2korr(*row);break;
			case 1:uval = (uint64_t) uint1korr(*row);break;
		}

#if SIZEOF_ZEND_LONG==4
		if (uval > INT_MAX) {
			DBG_INF("stringify");
			tmp_len = sprintf((char *)&tmp, MYSQLND_LLU_SPEC, uval);
		} else
#endif /* #if SIZEOF_LONG==4 */
		{
			if (byte_count < 8 || uval <= L64(9223372036854775807)) {
				ZVAL_LONG(zv, (zend_long) uval); /* the cast is safe, we are in the range */
			} else {
				DBG_INF("stringify");
				tmp_len = sprintf((char *)&tmp, MYSQLND_LLU_SPEC, uval);
				DBG_INF_FMT("value=%s", tmp);
			}
		}
	} else {
		/* SIGNED */
		int64_t lval = 0;
		switch (byte_count) {
			case 8:lval = (int64_t) sint8korr(*row);break;
			/*
			  7, 6 and 5 are not possible.
			  BIT is only unsigned, thus only uint5|6|7 macroses exist
			*/
			case 4:lval = (int64_t) sint4korr(*row);break;
			case 3:lval = (int64_t) sint3korr(*row);break;
			case 2:lval = (int64_t) sint2korr(*row);break;
			case 1:lval = (int64_t) *(int8_t*)*row;break;
		}

#if SIZEOF_ZEND_LONG==4
		if ((L64(2147483647) < (int64_t) lval) || (L64(-2147483648) > (int64_t) lval)) {
			DBG_INF("stringify");
			tmp_len = sprintf((char *)&tmp, MYSQLND_LL_SPEC, lval);
		} else
#endif /* SIZEOF */
		{
			ZVAL_LONG(zv, (zend_long) lval); /* the cast is safe, we are in the range */
		}
	}

	if (tmp_len) {
		ZVAL_STRINGL(zv, tmp, tmp_len);
	}
	(*row)+= byte_count;
	DBG_VOID_RETURN;
}