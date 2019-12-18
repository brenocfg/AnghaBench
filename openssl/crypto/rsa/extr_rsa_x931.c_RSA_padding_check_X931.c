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
 int /*<<< orphan*/  RSA_F_RSA_PADDING_CHECK_X931 ; 
 int /*<<< orphan*/  RSA_R_INVALID_HEADER ; 
 int /*<<< orphan*/  RSA_R_INVALID_PADDING ; 
 int /*<<< orphan*/  RSA_R_INVALID_TRAILER ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 

int RSA_padding_check_X931(unsigned char *to, int tlen,
                           const unsigned char *from, int flen, int num)
{
    int i = 0, j;
    const unsigned char *p;

    p = from;
    if ((num != flen) || ((*p != 0x6A) && (*p != 0x6B))) {
        RSAerr(RSA_F_RSA_PADDING_CHECK_X931, RSA_R_INVALID_HEADER);
        return -1;
    }

    if (*p++ == 0x6B) {
        j = flen - 3;
        for (i = 0; i < j; i++) {
            unsigned char c = *p++;
            if (c == 0xBA)
                break;
            if (c != 0xBB) {
                RSAerr(RSA_F_RSA_PADDING_CHECK_X931, RSA_R_INVALID_PADDING);
                return -1;
            }
        }

        j -= i;

        if (i == 0) {
            RSAerr(RSA_F_RSA_PADDING_CHECK_X931, RSA_R_INVALID_PADDING);
            return -1;
        }

    } else {
        j = flen - 2;
    }

    if (p[j] != 0xCC) {
        RSAerr(RSA_F_RSA_PADDING_CHECK_X931, RSA_R_INVALID_TRAILER);
        return -1;
    }

    memcpy(to, p, (unsigned int)j);

    return j;
}