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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_print (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,int,char*) ; 

__attribute__((used)) static int i2r_ocsp_acutoff(const X509V3_EXT_METHOD *method, void *cutoff,
                            BIO *bp, int ind)
{
    if (BIO_printf(bp, "%*s", ind, "") <= 0)
        return 0;
    if (!ASN1_GENERALIZEDTIME_print(bp, cutoff))
        return 0;
    return 1;
}