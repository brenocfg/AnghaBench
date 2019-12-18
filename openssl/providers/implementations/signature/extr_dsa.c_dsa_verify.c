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
struct TYPE_2__ {size_t mdsize; int /*<<< orphan*/  dsa; } ;
typedef  TYPE_1__ PROV_DSA_CTX ;

/* Variables and functions */
 int DSA_verify (int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_verify(void *vpdsactx, const unsigned char *sig, size_t siglen,
                      const unsigned char *tbs, size_t tbslen)
{
    PROV_DSA_CTX *pdsactx = (PROV_DSA_CTX *)vpdsactx;

    if (pdsactx->mdsize != 0 && tbslen != pdsactx->mdsize)
        return 0;

    return DSA_verify(0, tbs, tbslen, sig, siglen, pdsactx->dsa);
}