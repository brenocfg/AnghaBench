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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ASN1_item_d2i_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RSAPrivateKey ; 

RSA *d2i_RSAPrivateKey_bio(BIO *bp, RSA **rsa)
{
    return ASN1_item_d2i_bio(ASN1_ITEM_rptr(RSAPrivateKey), bp, rsa);
}