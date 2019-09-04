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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  geoStoreType ;

/* Variables and functions */
 int /*<<< orphan*/  STORE_COORD ; 
 int /*<<< orphan*/  STORE_DIST ; 
 int /*<<< orphan*/  STORE_NONE ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

geoStoreType get_georadius_store_type(zend_string *key) {
    if (ZSTR_LEN(key) == 5 && !strcasecmp(ZSTR_VAL(key), "store")) {
        return STORE_COORD;
    } else if (ZSTR_LEN(key) == 9 && !strcasecmp(ZSTR_VAL(key), "storedist")) {
        return STORE_DIST;
    }

    return STORE_NONE;
}