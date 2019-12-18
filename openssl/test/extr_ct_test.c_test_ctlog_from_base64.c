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
typedef  int /*<<< orphan*/  CTLOG ;

/* Variables and functions */
 int /*<<< orphan*/  CTLOG_new_from_base64 (int /*<<< orphan*/ **,char const*,char const*) ; 
 int /*<<< orphan*/  TEST_true (int) ; 

__attribute__((used)) static int test_ctlog_from_base64(void)
{
    CTLOG *ctlogp = NULL;
    const char notb64[] = "\01\02\03\04";
    const char pad[] = "====";
    const char name[] = "name";

    /* We expect these to both fail! */
    if (!TEST_true(!CTLOG_new_from_base64(&ctlogp, notb64, name))
        || !TEST_true(!CTLOG_new_from_base64(&ctlogp, pad, name)))
        return 0;
    return 1;
}