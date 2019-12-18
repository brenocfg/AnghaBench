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
 int /*<<< orphan*/  CRYPTO_F_OPENSSL_HEXSTR2BUF_EX ; 
 int /*<<< orphan*/  CRYPTO_R_ILLEGAL_HEX_DIGIT ; 
 int /*<<< orphan*/  CRYPTO_R_ODD_NUMBER_OF_DIGITS ; 
 int /*<<< orphan*/  CRYPTO_R_TOO_SMALL_BUFFER ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OPENSSL_hexchar2int (unsigned char) ; 

int OPENSSL_hexstr2buf_ex(unsigned char *buf, size_t buf_n, size_t *buflen,
                          const char *str)
{
    unsigned char *q;
    unsigned char ch, cl;
    int chi, cli;
    const unsigned char *p;
    size_t cnt;

    for (p = (const unsigned char *)str, q = buf, cnt = 0; *p; ) {
        ch = *p++;
        if (ch == ':')
            continue;
        cl = *p++;
        if (!cl) {
            CRYPTOerr(CRYPTO_F_OPENSSL_HEXSTR2BUF_EX,
                      CRYPTO_R_ODD_NUMBER_OF_DIGITS);
            return 0;
        }
        cli = OPENSSL_hexchar2int(cl);
        chi = OPENSSL_hexchar2int(ch);
        if (cli < 0 || chi < 0) {
            CRYPTOerr(CRYPTO_F_OPENSSL_HEXSTR2BUF_EX,
                      CRYPTO_R_ILLEGAL_HEX_DIGIT);
            return 0;
        }
        cnt++;
        if (q != NULL) {
            if (cnt > buf_n) {
                CRYPTOerr(CRYPTO_F_OPENSSL_HEXSTR2BUF_EX,
                          CRYPTO_R_TOO_SMALL_BUFFER);
                return 0;
            }
            *q++ = (unsigned char)((chi << 4) | cli);
        }
    }

    if (buflen != NULL)
        *buflen = cnt;
    return 1;
}