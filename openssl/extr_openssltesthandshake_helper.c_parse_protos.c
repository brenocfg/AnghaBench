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
 int /*<<< orphan*/  TEST_int_gt (size_t,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  TEST_ptr_null (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int parse_protos(const char *protos, unsigned char **out, size_t *outlen)
{
    size_t len, i, prefix;

    len = strlen(protos);

    /* Should never have reuse. */
    if (!TEST_ptr_null(*out)
            /* Test values are small, so we omit length limit checks. */
            || !TEST_ptr(*out = OPENSSL_malloc(len + 1)))
        return 0;
    *outlen = len + 1;

    /*
     * foo => '3', 'f', 'o', 'o'
     * foo,bar => '3', 'f', 'o', 'o', '3', 'b', 'a', 'r'
     */
    memcpy(*out + 1, protos, len);

    prefix = 0;
    i = prefix + 1;
    while (i <= len) {
        if ((*out)[i] == ',') {
            if (!TEST_int_gt(i - 1, prefix))
                goto err;
            (*out)[prefix] = (unsigned char)(i - 1 - prefix);
            prefix = i;
        }
        i++;
    }
    if (!TEST_int_gt(len, prefix))
        goto err;
    (*out)[prefix] = (unsigned char)(len - prefix);
    return 1;

err:
    OPENSSL_free(*out);
    *out = NULL;
    return 0;
}