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
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* i2s_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int asn1_print_integer(BIO *out, const ASN1_INTEGER *str)
{
    char *s;
    int ret = 1;
    s = i2s_ASN1_INTEGER(NULL, str);
    if (s == NULL)
        return 0;
    if (BIO_puts(out, s) <= 0)
        ret = 0;
    OPENSSL_free(s);
    return ret;
}