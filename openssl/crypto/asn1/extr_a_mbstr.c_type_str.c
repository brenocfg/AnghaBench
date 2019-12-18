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
 unsigned long B_ASN1_BMPSTRING ; 
 unsigned long B_ASN1_IA5STRING ; 
 unsigned long B_ASN1_NUMERICSTRING ; 
 unsigned long B_ASN1_PRINTABLESTRING ; 
 unsigned long B_ASN1_T61STRING ; 
 unsigned long INT_MAX ; 
 unsigned long ossl_fromascii (unsigned long) ; 
 int /*<<< orphan*/  ossl_isascii (int const) ; 
 int /*<<< orphan*/  ossl_isasn1print (int const) ; 
 scalar_t__ ossl_isdigit (int const) ; 

__attribute__((used)) static int type_str(unsigned long value, void *arg)
{
    unsigned long types = *((unsigned long *)arg);
    const int native = value > INT_MAX ? INT_MAX : ossl_fromascii(value);

    if ((types & B_ASN1_NUMERICSTRING) && !(ossl_isdigit(native)
                                            || native == ' '))
        types &= ~B_ASN1_NUMERICSTRING;
    if ((types & B_ASN1_PRINTABLESTRING) && !ossl_isasn1print(native))
        types &= ~B_ASN1_PRINTABLESTRING;
    if ((types & B_ASN1_IA5STRING) && !ossl_isascii(native))
        types &= ~B_ASN1_IA5STRING;
    if ((types & B_ASN1_T61STRING) && (value > 0xff))
        types &= ~B_ASN1_T61STRING;
    if ((types & B_ASN1_BMPSTRING) && (value > 0xffff))
        types &= ~B_ASN1_BMPSTRING;
    if (!types)
        return -1;
    *((unsigned long *)arg) = types;
    return 1;
}