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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2binpad (int /*<<< orphan*/  const*,unsigned char*,size_t) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 size_t BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MAX_STRING_WIDTH ; 
 int MEM_BUFFER_SIZE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 size_t bn_bytes ; 
 size_t convert_bn_memory (unsigned char*,size_t const,char*,int*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  test_bignum_header_line () ; 
 int /*<<< orphan*/  test_bignum_zero_print (int /*<<< orphan*/  const*,char) ; 
 int /*<<< orphan*/  test_diff_header (char const*,char const*) ; 
 int /*<<< orphan*/  test_fail_message_prefix (char const*,char const*,int,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  test_flush_stderr () ; 
 int /*<<< orphan*/  test_printf_stderr (char*,...) ; 

__attribute__((used)) static void test_fail_bignum_common(const char *prefix, const char *file,
                                    int line, const char *type,
                                    const char *left, const char *right,
                                    const char *op,
                                    const BIGNUM *bn1, const BIGNUM *bn2)
{
    const size_t bytes = bn_bytes;
    char b1[MAX_STRING_WIDTH + 1], b2[MAX_STRING_WIDTH + 1];
    char *p, bdiff[MAX_STRING_WIDTH + 1];
    size_t l1, l2, n1, n2, i, len;
    unsigned int cnt, diff, real_diff;
    unsigned char *m1 = NULL, *m2 = NULL;
    int lz1 = 1, lz2 = 1;
    unsigned char buffer[MEM_BUFFER_SIZE * 2], *bufp = buffer;

    test_fail_message_prefix(prefix, file, line, type, left, right, op);
    l1 = bn1 == NULL ? 0 : (BN_num_bytes(bn1) + (BN_is_negative(bn1) ? 1 : 0));
    l2 = bn2 == NULL ? 0 : (BN_num_bytes(bn2) + (BN_is_negative(bn2) ? 1 : 0));
    if (l1 == 0 && l2 == 0) {
        if ((bn1 == NULL) == (bn2 == NULL)) {
            test_bignum_header_line();
            test_bignum_zero_print(bn1, ' ');
        } else {
            test_diff_header(left, right);
            test_bignum_header_line();
            test_bignum_zero_print(bn1, '-');
            test_bignum_zero_print(bn2, '+');
        }
        goto fin;
    }

    if (l1 != l2 || bn1 == NULL || bn2 == NULL || BN_cmp(bn1, bn2) != 0)
        test_diff_header(left, right);
    test_bignum_header_line();

    len = ((l1 > l2 ? l1 : l2) + bytes - 1) / bytes * bytes;

    if (len > MEM_BUFFER_SIZE && (bufp = OPENSSL_malloc(len * 2)) == NULL) {
        bufp = buffer;
        len = MEM_BUFFER_SIZE;
        test_printf_stderr("WARNING: these BIGNUMs have been truncated\n");
    }

    if (bn1 != NULL) {
        m1 = bufp;
        BN_bn2binpad(bn1, m1, len);
    }
    if (bn2 != NULL) {
        m2 = bufp + len;
        BN_bn2binpad(bn2, m2, len);
    }

    while (len > 0) {
        cnt = 8 * (len - bytes);
        n1 = convert_bn_memory(m1, bytes, b1, &lz1, bn1);
        n2 = convert_bn_memory(m2, bytes, b2, &lz2, bn2);

        diff = real_diff = 0;
        i = 0;
        p = bdiff;
        for (i=0; b1[i] != '\0'; i++)
            if (b1[i] == b2[i] || b1[i] == ' ' || b2[i] == ' ') {
                *p++ = ' ';
                diff |= b1[i] != b2[i];
            } else {
                *p++ = '^';
                real_diff = diff = 1;
            }
        *p++ = '\0';
        if (!diff) {
            test_printf_stderr(" %s:% 5d\n", n2 > n1 ? b2 : b1, cnt);
        } else {
            if (cnt == 0 && bn1 == NULL)
                test_printf_stderr("-%s\n", b1);
            else if (cnt == 0 || n1 > 0)
                test_printf_stderr("-%s:% 5d\n", b1, cnt);
            if (cnt == 0 && bn2 == NULL)
                test_printf_stderr("+%s\n", b2);
            else if (cnt == 0 || n2 > 0)
                test_printf_stderr("+%s:% 5d\n", b2, cnt);
            if (real_diff && (cnt == 0 || (n1 > 0 && n2 > 0))
                    && bn1 != NULL && bn2 != NULL)
                test_printf_stderr(" %s\n", bdiff);
        }
        if (m1 != NULL)
            m1 += bytes;
        if (m2 != NULL)
            m2 += bytes;
        len -= bytes;
    }
fin:
    test_flush_stderr();
    if (bufp != buffer)
        OPENSSL_free(bufp);
}