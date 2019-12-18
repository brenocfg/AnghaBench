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
struct TYPE_4__ {int flags; int /*<<< orphan*/  Ni; int /*<<< orphan*/  N; int /*<<< orphan*/  RR; } ;
typedef  TYPE_1__ BN_MONT_CTX ;

/* Variables and functions */
 int BN_FLG_MALLOCED ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void BN_MONT_CTX_free(BN_MONT_CTX *mont)
{
    if (mont == NULL)
        return;
    BN_clear_free(&mont->RR);
    BN_clear_free(&mont->N);
    BN_clear_free(&mont->Ni);
    if (mont->flags & BN_FLG_MALLOCED)
        OPENSSL_free(mont);
}