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
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_PRINT_MAX_INDENT ; 
 scalar_t__ ASN1_buf_print (int /*<<< orphan*/ *,unsigned char*,int,int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int BN_BYTES ; 
 int BN_bn2bin (int /*<<< orphan*/  const*,unsigned char*) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 scalar_t__* bn_get_words (int /*<<< orphan*/  const*) ; 

int ASN1_bn_print(BIO *bp, const char *number, const BIGNUM *num,
                  unsigned char *ign, int indent)
{
    int n, rv = 0;
    const char *neg;
    unsigned char *buf = NULL, *tmp = NULL;
    int buflen;

    if (num == NULL)
        return 1;
    neg = BN_is_negative(num) ? "-" : "";
    if (!BIO_indent(bp, indent, ASN1_PRINT_MAX_INDENT))
        return 0;
    if (BN_is_zero(num)) {
        if (BIO_printf(bp, "%s 0\n", number) <= 0)
            return 0;
        return 1;
    }

    if (BN_num_bytes(num) <= BN_BYTES) {
        if (BIO_printf(bp, "%s %s%lu (%s0x%lx)\n", number, neg,
                       (unsigned long)bn_get_words(num)[0], neg,
                       (unsigned long)bn_get_words(num)[0]) <= 0)
            return 0;
        return 1;
    }

    buflen = BN_num_bytes(num) + 1;
    buf = tmp = OPENSSL_malloc(buflen);
    if (buf == NULL)
        goto err;
    buf[0] = 0;
    if (BIO_printf(bp, "%s%s\n", number,
                   (neg[0] == '-') ? " (Negative)" : "") <= 0)
        goto err;
    n = BN_bn2bin(num, buf + 1);

    if (buf[1] & 0x80)
        n++;
    else
        tmp++;

    if (ASN1_buf_print(bp, tmp, n, indent + 4) == 0)
        goto err;
    rv = 1;
    err:
    OPENSSL_clear_free(buf, buflen);
    return rv;
}