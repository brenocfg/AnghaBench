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
 int /*<<< orphan*/  TEST_error (char*,char*) ; 
 int /*<<< orphan*/  TEST_info (char*,char*) ; 

__attribute__((used)) static int test_messages(void)
{
    TEST_info("This is an %s message.", "info");
    TEST_error("This is an %s message.", "error");
    return 1;
}