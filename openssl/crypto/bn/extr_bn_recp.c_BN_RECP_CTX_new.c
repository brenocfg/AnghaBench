#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  Nr; int /*<<< orphan*/  N; } ;
typedef  TYPE_1__ BN_RECP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_F_BN_RECP_CTX_NEW ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  bn_init (int /*<<< orphan*/ *) ; 

BN_RECP_CTX *BN_RECP_CTX_new(void)
{
    BN_RECP_CTX *ret;

    if ((ret = OPENSSL_zalloc(sizeof(*ret))) == NULL) {
        BNerr(BN_F_BN_RECP_CTX_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    bn_init(&(ret->N));
    bn_init(&(ret->Nr));
    ret->flags = BN_FLG_MALLOCED;
    return ret;
}