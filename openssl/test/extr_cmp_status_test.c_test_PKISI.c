#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* str; char* text; int pkifailure; int /*<<< orphan*/  pkistatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_STATUS_TEST_FIXTURE ; 
 int /*<<< orphan*/  EXECUTE_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OSSL_CMP_CTX_FAILINFO_badDataFormat ; 
 int OSSL_CMP_CTX_FAILINFO_unsupportedVersion ; 
 int /*<<< orphan*/  OSSL_CMP_PKISTATUS_revocationNotification ; 
 int /*<<< orphan*/  SETUP_TEST_FIXTURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_PKISI_test ; 
 TYPE_1__* fixture ; 
 int result ; 
 int /*<<< orphan*/  set_up ; 
 int /*<<< orphan*/  tear_down ; 

__attribute__((used)) static int test_PKISI(void)
{
    SETUP_TEST_FIXTURE(CMP_STATUS_TEST_FIXTURE, set_up);
    fixture->pkistatus = OSSL_CMP_PKISTATUS_revocationNotification;
    fixture->str = "PKIStatus: revocation notification - a revocation of the cert has occurred";
    fixture->text = "this is an additional text describing the failure";
    fixture->pkifailure = OSSL_CMP_CTX_FAILINFO_unsupportedVersion |
        OSSL_CMP_CTX_FAILINFO_badDataFormat;
    EXECUTE_TEST(execute_PKISI_test, tear_down);
    return result;
}