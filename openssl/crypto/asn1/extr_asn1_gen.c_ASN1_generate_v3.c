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
typedef  int /*<<< orphan*/  X509V3_CTX ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_GENERATE_V3 ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * generate_v3 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

ASN1_TYPE *ASN1_generate_v3(const char *str, X509V3_CTX *cnf)
{
    int err = 0;
    ASN1_TYPE *ret = generate_v3(str, cnf, 0, &err);
    if (err)
        ASN1err(ASN1_F_ASN1_GENERATE_V3, err);
    return ret;
}