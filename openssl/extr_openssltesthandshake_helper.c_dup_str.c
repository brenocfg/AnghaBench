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
 char* OPENSSL_strndup (char const*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_strnlen (char const*,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 scalar_t__ TEST_size_t_eq (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static char *dup_str(const unsigned char *in, size_t len)
{
    char *ret = NULL;

    if (len == 0)
        return NULL;

    /* Assert that the string does not contain NUL-bytes. */
    if (TEST_size_t_eq(OPENSSL_strnlen((const char*)(in), len), len))
        TEST_ptr(ret = OPENSSL_strndup((const char*)(in), len));
    return ret;
}