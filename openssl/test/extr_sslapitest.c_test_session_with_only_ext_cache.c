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
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int execute_test_session (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_session_with_only_ext_cache(void)
{
#ifndef OPENSSL_NO_TLS1_3
    if (!execute_test_session(TLS1_3_VERSION, 0, 1))
        return 0;
#endif

#ifndef OPENSSL_NO_TLS1_2
    return execute_test_session(TLS1_2_VERSION, 0, 1);
#else
    return 1;
#endif
}