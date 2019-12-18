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
typedef  char uint8_t ;
typedef  int ossl_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int OPENSSL_hexchar2int (char const) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  _UC (char const) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static ossl_ssize_t hexdecode(const char *in, void *result)
{
    unsigned char **out = (unsigned char **)result;
    unsigned char *ret;
    unsigned char *cp;
    uint8_t byte;
    int nibble = 0;

    if (!TEST_ptr(ret = OPENSSL_malloc(strlen(in) / 2)))
        return -1;
    cp = ret;

    for (byte = 0; *in; ++in) {
        int x;

        if (isspace(_UC(*in)))
            continue;
        x = OPENSSL_hexchar2int(*in);
        if (x < 0) {
            OPENSSL_free(ret);
            return 0;
        }
        byte |= (char)x;
        if ((nibble ^= 1) == 0) {
            *cp++ = byte;
            byte = 0;
        } else {
            byte <<= 4;
        }
    }
    if (nibble != 0) {
        OPENSSL_free(ret);
        return 0;
    }

    return cp - (*out = ret);
}