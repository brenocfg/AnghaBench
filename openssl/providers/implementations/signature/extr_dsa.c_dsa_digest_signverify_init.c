#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * mdctx; int /*<<< orphan*/  mdsize; int /*<<< orphan*/ * md; int /*<<< orphan*/  libctx; } ;
typedef  TYPE_1__ PROV_DSA_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/ * EVP_MD_fetch (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  EVP_MD_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_signature_init (void*,void*) ; 

__attribute__((used)) static int dsa_digest_signverify_init(void *vpdsactx, const char *mdname,
                                      const char *props, void *vdsa)
{
    PROV_DSA_CTX *pdsactx = (PROV_DSA_CTX *)vpdsactx;
    EVP_MD *md;

    if (!dsa_signature_init(vpdsactx, vdsa))
        return 0;

    md = EVP_MD_fetch(pdsactx->libctx, mdname, props);
    if (md == NULL)
        return 0;
    pdsactx->md = md;
    pdsactx->mdsize = EVP_MD_size(md);
    pdsactx->mdctx = EVP_MD_CTX_new();
    if (pdsactx->mdctx == NULL)
        return 0;

    if (!EVP_DigestInit_ex(pdsactx->mdctx, md, NULL))
        return 0;

    return 1;
}