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
typedef  int /*<<< orphan*/  SCT_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_SCT_CTX_NEW ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

SCT_CTX *SCT_CTX_new(void)
{
    SCT_CTX *sctx = OPENSSL_zalloc(sizeof(*sctx));

    if (sctx == NULL)
        CTerr(CT_F_SCT_CTX_NEW, ERR_R_MALLOC_FAILURE);

    return sctx;
}