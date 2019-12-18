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
struct TYPE_2__ {unsigned long long epoch_time_in_ms; char* certificate_file; char* issuer_file; int expected_sct_count; int test_validity; scalar_t__ expected_valid_sct_count; int /*<<< orphan*/  certs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXECUTE_CT_TEST () ; 
 int /*<<< orphan*/  SETUP_CT_TEST_FIXTURE () ; 
 int /*<<< orphan*/  certs_dir ; 
 TYPE_1__* fixture ; 
 int result ; 

__attribute__((used)) static int test_verify_fails_for_future_sct(void)
{
    SETUP_CT_TEST_FIXTURE();
    if (fixture == NULL)
        return 0;
    fixture->epoch_time_in_ms = 1365094800000ULL; /* Apr 4 17:00:00 2013 GMT */
    fixture->certs_dir = certs_dir;
    fixture->certificate_file = "embeddedSCTs1.pem";
    fixture->issuer_file = "embeddedSCTs1_issuer.pem";
    fixture->expected_sct_count = 1;
    fixture->expected_valid_sct_count = 0;
    fixture->test_validity = 1;
    EXECUTE_CT_TEST();
    return result;
}