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
 unsigned char* OPENSSL_hexstr2buf (char const*,long*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  TEST_info (char*,char const*) ; 
 int /*<<< orphan*/  TEST_openssl_errors () ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char const*) ; 
 unsigned char* unescape (char const*,size_t,size_t*) ; 

__attribute__((used)) static int parse_bin(const char *value, unsigned char **buf, size_t *buflen)
{
    long len;

    /* Check for NULL literal */
    if (strcmp(value, "NULL") == 0) {
        *buf = NULL;
        *buflen = 0;
        return 1;
    }

    /* Check for empty value */
    if (*value == '\0') {
        /*
         * Don't return NULL for zero length buffer. This is needed for
         * some tests with empty keys: HMAC_Init_ex() expects a non-NULL key
         * buffer even if the key length is 0, in order to detect key reset.
         */
        *buf = OPENSSL_malloc(1);
        if (*buf == NULL)
            return 0;
        **buf = 0;
        *buflen = 0;
        return 1;
    }

    /* Check for string literal */
    if (value[0] == '"') {
        size_t vlen = strlen(++value);

        if (vlen == 0 || value[vlen - 1] != '"')
            return 0;
        vlen--;
        *buf = unescape(value, vlen, buflen);
        return *buf == NULL ? 0 : 1;
    }

    /* Otherwise assume as hex literal and convert it to binary buffer */
    if (!TEST_ptr(*buf = OPENSSL_hexstr2buf(value, &len))) {
        TEST_info("Can't convert %s", value);
        TEST_openssl_errors();
        return -1;
    }
    /* Size of input buffer means we'll never overflow */
    *buflen = len;
    return 1;
}