#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* member_0; scalar_t__ code; int /*<<< orphan*/  str; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ error_enum ;
struct TYPE_6__ {int /*<<< orphan*/  sname; } ;
typedef  TYPE_2__ ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
#define  ASN1_BIO 132 
#define  ASN1_COMPARE 131 
#define  ASN1_DECODE 130 
#define  ASN1_ENCODE 129 
 TYPE_2__* ASN1_ITEM_get (size_t) ; 
 int /*<<< orphan*/ * ASN1_ITEM_lookup (char const*) ; 
#define  ASN1_OK 128 
 scalar_t__ ASN1_UNKNOWN ; 
 size_t OSSL_NELEM (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_error (char*,char const*) ; 
 int /*<<< orphan*/  TEST_note (char*,...) ; 
 int /*<<< orphan*/  TEST_ptr (char const*) ; 
 scalar_t__ expected_error ; 
 int /*<<< orphan*/ * item_type ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  test_bad_asn1 ; 
 char const* test_file ; 
 char* test_get_argument (int) ; 

int setup_tests(void)
{
    const char *test_type_name;
    const char *expected_error_string;

    size_t i;

    static error_enum expected_errors[] = {
        {"OK", ASN1_OK},
        {"BIO", ASN1_BIO},
        {"decode", ASN1_DECODE},
        {"encode", ASN1_ENCODE},
        {"compare", ASN1_COMPARE}
    };

    if (!TEST_ptr(test_type_name = test_get_argument(0))
            || !TEST_ptr(expected_error_string = test_get_argument(1))
            || !TEST_ptr(test_file = test_get_argument(2)))
        return 0;

    item_type = ASN1_ITEM_lookup(test_type_name);

    if (item_type == NULL) {
        TEST_error("Unknown type %s", test_type_name);
        TEST_note("Supported types:");
        for (i = 0;; i++) {
            const ASN1_ITEM *it = ASN1_ITEM_get(i);

            if (it == NULL)
                break;
            TEST_note("\t%s", it->sname);
        }
        return 0;
    }

    for (i = 0; i < OSSL_NELEM(expected_errors); i++) {
        if (strcmp(expected_errors[i].str, expected_error_string) == 0) {
            expected_error = expected_errors[i].code;
            break;
        }
    }

    if (expected_error == ASN1_UNKNOWN) {
        TEST_error("Unknown expected error %s\n", expected_error_string);
        return 0;
    }

    ADD_TEST(test_bad_asn1);
    return 1;
}