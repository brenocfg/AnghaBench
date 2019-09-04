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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_PCTX ;

/* Variables and functions */
 int pkey_rsa_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static int rsa_priv_print(BIO *bp, const EVP_PKEY *pkey, int indent,
                          ASN1_PCTX *ctx)
{
    return pkey_rsa_print(bp, pkey, indent, 1);
}