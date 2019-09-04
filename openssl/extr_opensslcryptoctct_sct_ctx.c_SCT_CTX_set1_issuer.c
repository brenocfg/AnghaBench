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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SCT_CTX ;

/* Variables and functions */
 int SCT_CTX_set1_issuer_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_X509_PUBKEY (int /*<<< orphan*/  const*) ; 

int SCT_CTX_set1_issuer(SCT_CTX *sctx, const X509 *issuer)
{
    return SCT_CTX_set1_issuer_pubkey(sctx, X509_get_X509_PUBKEY(issuer));
}