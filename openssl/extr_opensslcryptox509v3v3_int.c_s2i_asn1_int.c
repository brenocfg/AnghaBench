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
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
typedef  int /*<<< orphan*/  X509V3_CTX ;

/* Variables and functions */
 void* s2i_ASN1_INTEGER (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void *s2i_asn1_int(X509V3_EXT_METHOD *meth, X509V3_CTX *ctx,
                          const char *value)
{
    return s2i_ASN1_INTEGER(meth, value);
}