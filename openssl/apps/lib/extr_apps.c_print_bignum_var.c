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
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int BN_bn2bin (int /*<<< orphan*/  const*,unsigned char*) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 

void print_bignum_var(BIO *out, const BIGNUM *in, const char *var,
                      int len, unsigned char *buffer)
{
    BIO_printf(out, "    static unsigned char %s_%d[] = {", var, len);
    if (BN_is_zero(in)) {
        BIO_printf(out, "\n        0x00");
    } else {
        int i, l;

        l = BN_bn2bin(in, buffer);
        for (i = 0; i < l; i++) {
            BIO_printf(out, (i % 10) == 0 ? "\n        " : " ");
            if (i < l - 1)
                BIO_printf(out, "0x%02X,", buffer[i]);
            else
                BIO_printf(out, "0x%02X", buffer[i]);
        }
    }
    BIO_printf(out, "\n    };\n");
}