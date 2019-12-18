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
struct cal_entry_t {int num_months; int /*<<< orphan*/  symbol; int /*<<< orphan*/  name; int /*<<< orphan*/  max_days_in_month; int /*<<< orphan*/ * month_name_short; int /*<<< orphan*/ * month_name_long; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_index_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 struct cal_entry_t* cal_conversion_table ; 

__attribute__((used)) static void _php_cal_info(int cal, zval *ret)
{
	zval months, smonths;
	int i;
	const struct cal_entry_t *calendar;

	calendar = &cal_conversion_table[cal];
	array_init(ret);

	array_init(&months);
	array_init(&smonths);

	for (i = 1; i <= calendar->num_months; i++) {
		add_index_string(&months, i, calendar->month_name_long[i]);
		add_index_string(&smonths, i, calendar->month_name_short[i]);
	}

	add_assoc_zval(ret, "months", &months);
	add_assoc_zval(ret, "abbrevmonths", &smonths);
	add_assoc_long(ret, "maxdaysinmonth", calendar->max_days_in_month);
	add_assoc_string(ret, "calname", calendar->name);
	add_assoc_string(ret, "calsymbol", calendar->symbol);

}