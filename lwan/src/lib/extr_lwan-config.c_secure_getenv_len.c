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
 size_t ENV_VAR_NAME_LEN_MAX ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  lwan_status_error (char*,size_t) ; 
 char const* secure_getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strndupa (char const*,size_t) ; 

__attribute__((used)) static __attribute__((noinline)) const char *secure_getenv_len(const char *key, size_t len)
{
    if (UNLIKELY(len > ENV_VAR_NAME_LEN_MAX)) {
        lwan_status_error("Variable name exceeds %d bytes", ENV_VAR_NAME_LEN_MAX);
        return NULL;
    }

    return secure_getenv(strndupa(key, len));
}