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
typedef  int /*<<< orphan*/  timelib_tzinfo ;
typedef  int /*<<< orphan*/  timelib_tzdb ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_HASHTABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _php_date_tzinfo_dtor ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * timelib_parse_tzfile (char*,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  tzcache ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_str_add_ptr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_hash_str_find_ptr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static timelib_tzinfo *php_date_parse_tzfile(char *formal_tzname, const timelib_tzdb *tzdb)
{
	timelib_tzinfo *tzi;
	int dummy_error_code;

	if(!DATEG(tzcache)) {
		ALLOC_HASHTABLE(DATEG(tzcache));
		zend_hash_init(DATEG(tzcache), 4, NULL, _php_date_tzinfo_dtor, 0);
	}

	if ((tzi = zend_hash_str_find_ptr(DATEG(tzcache), formal_tzname, strlen(formal_tzname))) != NULL) {
		return tzi;
	}

	tzi = timelib_parse_tzfile(formal_tzname, tzdb, &dummy_error_code);
	if (tzi) {
		zend_hash_str_add_ptr(DATEG(tzcache), formal_tzname, strlen(formal_tzname), tzi);
	}
	return tzi;
}