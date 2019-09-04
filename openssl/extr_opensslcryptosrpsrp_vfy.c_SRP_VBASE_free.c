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
struct TYPE_4__ {struct TYPE_4__* seed_key; int /*<<< orphan*/  gN_cache; int /*<<< orphan*/  users_pwd; } ;
typedef  TYPE_1__ SRP_VBASE ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  SRP_user_pwd_free ; 
 int /*<<< orphan*/  sk_SRP_gN_cache_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_SRP_user_pwd_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void SRP_VBASE_free(SRP_VBASE *vb)
{
    if (!vb)
        return;
    sk_SRP_user_pwd_pop_free(vb->users_pwd, SRP_user_pwd_free);
    sk_SRP_gN_cache_free(vb->gN_cache);
    OPENSSL_free(vb->seed_key);
    OPENSSL_free(vb);
}