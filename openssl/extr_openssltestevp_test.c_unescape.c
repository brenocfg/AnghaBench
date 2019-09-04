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
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 unsigned char* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 

__attribute__((used)) static unsigned char* unescape(const char *input, size_t input_len,
                               size_t *out_len)
{
    unsigned char *ret, *p;
    size_t i;

    if (input_len == 0) {
        *out_len = 0;
        return OPENSSL_zalloc(1);
    }

    /* Escaping is non-expanding; over-allocate original size for simplicity. */
    if (!TEST_ptr(ret = p = OPENSSL_malloc(input_len)))
        return NULL;

    for (i = 0; i < input_len; i++) {
        if (*input == '\\') {
            if (i == input_len - 1 || *++input != 'n') {
                TEST_error("Bad escape sequence in file");
                goto err;
            }
            *p++ = '\n';
            i++;
            input++;
        } else {
            *p++ = *input++;
        }
    }

    *out_len = p - ret;
    return ret;

 err:
    OPENSSL_free(ret);
    return NULL;
}