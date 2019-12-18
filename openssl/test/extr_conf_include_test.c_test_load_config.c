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

/* Variables and functions */
 int /*<<< orphan*/  CONF_modules_load (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long ERR_peek_error () ; 
 long NCONF_get_number (int /*<<< orphan*/ ,char*,char*,long*) ; 
 char* NCONF_get_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  NCONF_load_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  TEST_int_eq (long,int) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_note (char*,...) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,char*) ; 
 int /*<<< orphan*/  conf ; 
 scalar_t__ expect_failure ; 
 int /*<<< orphan*/  in ; 

__attribute__((used)) static int test_load_config(void)
{
    long errline;
    long val;
    char *str;
    long err;

    if (!TEST_int_gt(NCONF_load_bio(conf, in, &errline), 0)
        || !TEST_int_eq(err = ERR_peek_error(), 0)) {
        if (expect_failure)
            return 1;
        TEST_note("Failure loading the configuration at line %ld", errline);
        return 0;
    }
    if (expect_failure) {
        TEST_note("Failure expected but did not happen");
        return 0;
    }

    if (!TEST_int_gt(CONF_modules_load(conf, NULL, 0), 0)) {
        TEST_note("Failed in CONF_modules_load");
        return 0;
    }

    /* verify whether RANDFILE is set correctly */
    str = NCONF_get_string(conf, "", "RANDFILE");
    if (!TEST_ptr(str) || !TEST_str_eq(str, "./.rnd")) {
        TEST_note("RANDFILE incorrect");
        return 0;
    }

    /* verify whether CA_default/default_days is set */
    val = 0;
    if (!TEST_int_eq(NCONF_get_number(conf, "CA_default", "default_days", &val), 1)
        || !TEST_int_eq(val, 365)) {
        TEST_note("default_days incorrect");
        return 0;
    }

    /* verify whether req/default_bits is set */
    val = 0;
    if (!TEST_int_eq(NCONF_get_number(conf, "req", "default_bits", &val), 1)
        || !TEST_int_eq(val, 2048)) {
        TEST_note("default_bits incorrect");
        return 0;
    }

    /* verify whether countryName_default is set correctly */
    str = NCONF_get_string(conf, "req_distinguished_name", "countryName_default");
    if (!TEST_ptr(str) || !TEST_str_eq(str, "AU")) {
        TEST_note("countryName_default incorrect");
        return 0;
    }

    return 1;
}