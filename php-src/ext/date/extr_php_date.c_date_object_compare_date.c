#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {TYPE_2__* time; } ;
typedef  TYPE_1__ php_date_obj ;
struct TYPE_7__ {int /*<<< orphan*/  tz_info; int /*<<< orphan*/  sse_uptodate; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/  ZEND_COMPARE_OBJECTS_FALLBACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_PHPDATE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int timelib_time_compare (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  timelib_update_ts (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int date_object_compare_date(zval *d1, zval *d2) /* {{{ */
{
	php_date_obj *o1;
	php_date_obj *o2;

	ZEND_COMPARE_OBJECTS_FALLBACK(d1, d2);

	o1 = Z_PHPDATE_P(d1);
	o2 = Z_PHPDATE_P(d2);

	if (!o1->time || !o2->time) {
		php_error_docref(NULL, E_WARNING, "Trying to compare an incomplete DateTime or DateTimeImmutable object");
		return 1;
	}
	if (!o1->time->sse_uptodate) {
		timelib_update_ts(o1->time, o1->time->tz_info);
	}
	if (!o2->time->sse_uptodate) {
		timelib_update_ts(o2->time, o2->time->tz_info);
	}

	return timelib_time_compare(o1->time, o2->time);
}