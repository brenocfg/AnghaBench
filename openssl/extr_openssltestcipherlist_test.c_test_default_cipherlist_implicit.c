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
 int /*<<< orphan*/  EXECUTE_CIPHERLIST_TEST () ; 
 int /*<<< orphan*/  SETUP_CIPHERLIST_TEST_FIXTURE () ; 
 int /*<<< orphan*/ * fixture ; 
 int result ; 

__attribute__((used)) static int test_default_cipherlist_implicit(void)
{
    SETUP_CIPHERLIST_TEST_FIXTURE();
    if (fixture == NULL)
        return 0;
    EXECUTE_CIPHERLIST_TEST();
    return result;
}