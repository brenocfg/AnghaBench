#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* test_case_name; } ;
typedef  TYPE_1__ CMP_ASN_TEST_FIXTURE ;

/* Variables and functions */
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 

__attribute__((used)) static CMP_ASN_TEST_FIXTURE *set_up(const char *const test_case_name)
{
    CMP_ASN_TEST_FIXTURE *fixture;

    if (!TEST_ptr(fixture = OPENSSL_zalloc(sizeof(*fixture))))
        return NULL;
    fixture->test_case_name = test_case_name;
    return fixture;
}