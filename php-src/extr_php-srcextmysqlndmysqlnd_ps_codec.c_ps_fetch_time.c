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
typedef  int zend_ulong ;
typedef  scalar_t__ zend_uchar ;
typedef  scalar_t__ zend_bool ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t ;
struct st_mysqlnd_time {int day; unsigned int hour; unsigned int minute; unsigned int second; int second_part; scalar_t__ neg; void* time_type; scalar_t__ month; scalar_t__ year; } ;
struct TYPE_3__ {int decimals; } ;
typedef  TYPE_1__ MYSQLND_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ENTER (char*) ; 
 int /*<<< orphan*/  DBG_INF_FMT (char*,char*) ; 
 int /*<<< orphan*/  DBG_VOID_RETURN ; 
 void* MYSQLND_TIMESTAMP_TIME ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct st_mysqlnd_time*,int /*<<< orphan*/ ,int) ; 
 int mnd_sprintf (char**,int /*<<< orphan*/ ,char*,char*,int,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  mnd_sprintf_free (char*) ; 
 int php_mysqlnd_net_field_length (scalar_t__ const**) ; 
 int pow (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sint4korr (scalar_t__ const*) ; 

__attribute__((used)) static void
ps_fetch_time(zval * zv, const MYSQLND_FIELD * const field, const unsigned int pack_len, const zend_uchar ** row)
{
	struct st_mysqlnd_time t;
	zend_ulong length; /* First byte encodes the length*/
	char * value;
	DBG_ENTER("ps_fetch_time");

	if ((length = php_mysqlnd_net_field_length(row))) {
		const zend_uchar * to = *row;

		t.time_type = MYSQLND_TIMESTAMP_TIME;
		t.neg			= (zend_bool) to[0];

		t.day			= (zend_ulong) sint4korr(to+1);
		t.hour			= (unsigned int) to[5];
		t.minute		= (unsigned int) to[6];
		t.second		= (unsigned int) to[7];
		t.second_part	= (length > 8) ? (zend_ulong) sint4korr(to+8) : 0;
		t.year			= t.month= 0;
		if (t.day) {
			/* Convert days to hours at once */
			t.hour += t.day*24;
			t.day	= 0;
		}

		(*row) += length;
	} else {
		memset(&t, 0, sizeof(t));
		t.time_type = MYSQLND_TIMESTAMP_TIME;
	}

    if (field->decimals > 0 && field->decimals < 7) {
        length = mnd_sprintf(
            &value,
            0,
            "%s%02u:%02u:%02u.%0*u",
            (t.neg ? "-" : ""),
            t.hour,
            t.minute,
            t.second,
            field->decimals,
           (uint32_t) (t.second_part / pow(10, 6 - field->decimals))
        );
    } else {
        length = mnd_sprintf(&value, 0, "%s%02u:%02u:%02u", (t.neg ? "-" : ""), t.hour, t.minute, t.second);
    }

	DBG_INF_FMT("%s", value);
	ZVAL_STRINGL(zv, value, length);
	mnd_sprintf_free(value);
	DBG_VOID_RETURN;
}