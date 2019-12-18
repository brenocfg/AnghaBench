#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ BN_MONT_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_F_BN_MONT_CTX_NEW ; 
 int /*<<< orphan*/  BN_MONT_CTX_init (TYPE_1__*) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_malloc (int) ; 

BN_MONT_CTX *BN_MONT_CTX_new(void)
{
    BN_MONT_CTX *ret;

    if ((ret = OPENSSL_malloc(sizeof(*ret))) == NULL) {
        BNerr(BN_F_BN_MONT_CTX_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    BN_MONT_CTX_init(ret);
    ret->flags = BN_FLG_MALLOCED;
    return ret;
}