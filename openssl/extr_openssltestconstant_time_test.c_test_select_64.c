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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CONSTTIME_FALSE_64 ; 
 int /*<<< orphan*/  CONSTTIME_TRUE_64 ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ constant_time_select_64 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int test_select_64(uint64_t a, uint64_t b)
{
    uint64_t selected = constant_time_select_64(CONSTTIME_TRUE_64, a, b);

    if (selected != a) {
        TEST_error("test_select_64 TRUE failed");
        BIO_printf(bio_err, "a=%jx b=%jx got %jx wanted a\n", a, b, selected);
        return 0;
    }
    selected = constant_time_select_64(CONSTTIME_FALSE_64, a, b);
    if (selected != b) {
        BIO_printf(bio_err, "a=%jx b=%jx got %jx wanted b\n", a, b, selected);
        return 0;
    }
    return 1;
}