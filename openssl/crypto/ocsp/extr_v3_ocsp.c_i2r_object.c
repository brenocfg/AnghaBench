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
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,int,char*) ; 
 scalar_t__ i2a_ASN1_OBJECT (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int i2r_object(const X509V3_EXT_METHOD *method, void *oid, BIO *bp,
                      int ind)
{
    if (BIO_printf(bp, "%*s", ind, "") <= 0)
        return 0;
    if (i2a_ASN1_OBJECT(bp, oid) <= 0)
        return 0;
    return 1;
}