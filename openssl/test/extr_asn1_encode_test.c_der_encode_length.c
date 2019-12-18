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
 int /*<<< orphan*/  OPENSSL_assert (int) ; 

__attribute__((used)) static size_t der_encode_length(size_t len, unsigned char **pp)
{
    size_t lenbytes;

    OPENSSL_assert(len < 0x8000);
    if (len > 255)
        lenbytes = 3;
    else if (len > 127)
        lenbytes = 2;
    else
        lenbytes = 1;

    if (pp != NULL) {
        if (lenbytes == 1) {
            *(*pp)++ = (unsigned char)len;
        } else {
            *(*pp)++ = (unsigned char)(lenbytes - 1);
            if (lenbytes == 2) {
                *(*pp)++ = (unsigned char)(0x80 | len);
            } else {
                *(*pp)++ = (unsigned char)(0x80 | (len >> 8));
                *(*pp)++ = (unsigned char)(len);
            }
        }
    }
    return lenbytes;
}