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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERROR_INVALID_FUNCTION ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int preserves_system_error(void)
{
#if defined(OPENSSL_SYS_WINDOWS)
    SetLastError(ERROR_INVALID_FUNCTION);
    ERR_get_error();
    return TEST_int_eq(GetLastError(), ERROR_INVALID_FUNCTION);
#else
    errno = EINVAL;
    ERR_get_error();
    return TEST_int_eq(errno, EINVAL);
#endif
}