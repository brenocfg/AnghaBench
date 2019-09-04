#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_object ;
typedef  int /*<<< orphan*/  zend_long ;
struct TYPE_7__ {TYPE_2__* diff; int /*<<< orphan*/  initialized; } ;
typedef  TYPE_3__ php_interval_obj ;
struct TYPE_5__ {scalar_t__ amount; scalar_t__ type; } ;
struct TYPE_6__ {int days; scalar_t__ have_special_relative; scalar_t__ have_weekday_relative; TYPE_1__ special; scalar_t__ invert; scalar_t__ first_last_day_of; scalar_t__ weekday_behavior; scalar_t__ weekday; scalar_t__ us; scalar_t__ s; scalar_t__ i; scalar_t__ h; scalar_t__ d; scalar_t__ m; scalar_t__ y; } ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_DOUBLE (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  ZVAL_FALSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* php_interval_obj_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_properties (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HashTable *date_object_get_properties_interval(zend_object *object) /* {{{ */
{
	HashTable *props;
	zval zv;
	php_interval_obj *intervalobj;

	intervalobj = php_interval_obj_from_obj(object);
	props = zend_std_get_properties(object);
	if (!intervalobj->initialized) {
		return props;
	}

#define PHP_DATE_INTERVAL_ADD_PROPERTY(n,f) \
	ZVAL_LONG(&zv, (zend_long)intervalobj->diff->f); \
	zend_hash_str_update(props, n, sizeof(n)-1, &zv);

	PHP_DATE_INTERVAL_ADD_PROPERTY("y", y);
	PHP_DATE_INTERVAL_ADD_PROPERTY("m", m);
	PHP_DATE_INTERVAL_ADD_PROPERTY("d", d);
	PHP_DATE_INTERVAL_ADD_PROPERTY("h", h);
	PHP_DATE_INTERVAL_ADD_PROPERTY("i", i);
	PHP_DATE_INTERVAL_ADD_PROPERTY("s", s);
	ZVAL_DOUBLE(&zv, (double)intervalobj->diff->us / 1000000.0);
	zend_hash_str_update(props, "f", sizeof("f") - 1, &zv);
	PHP_DATE_INTERVAL_ADD_PROPERTY("weekday", weekday);
	PHP_DATE_INTERVAL_ADD_PROPERTY("weekday_behavior", weekday_behavior);
	PHP_DATE_INTERVAL_ADD_PROPERTY("first_last_day_of", first_last_day_of);
	PHP_DATE_INTERVAL_ADD_PROPERTY("invert", invert);
	if (intervalobj->diff->days != -99999) {
		PHP_DATE_INTERVAL_ADD_PROPERTY("days", days);
	} else {
		ZVAL_FALSE(&zv);
		zend_hash_str_update(props, "days", sizeof("days")-1, &zv);
	}
	PHP_DATE_INTERVAL_ADD_PROPERTY("special_type", special.type);
	PHP_DATE_INTERVAL_ADD_PROPERTY("special_amount", special.amount);
	PHP_DATE_INTERVAL_ADD_PROPERTY("have_weekday_relative", have_weekday_relative);
	PHP_DATE_INTERVAL_ADD_PROPERTY("have_special_relative", have_special_relative);

	return props;
}