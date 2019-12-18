#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  md; int /*<<< orphan*/  mdctx; int /*<<< orphan*/  dsa; } ;
typedef  TYPE_1__ PROV_DSA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_MD_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void dsa_freectx(void *vpdsactx)
{
    PROV_DSA_CTX *pdsactx = (PROV_DSA_CTX *)vpdsactx;

    DSA_free(pdsactx->dsa);
    EVP_MD_CTX_free(pdsactx->mdctx);
    EVP_MD_free(pdsactx->md);

    OPENSSL_free(pdsactx);
}