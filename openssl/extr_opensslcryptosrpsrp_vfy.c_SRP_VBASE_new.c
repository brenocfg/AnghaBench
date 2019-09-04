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
struct TYPE_5__ {int /*<<< orphan*/ * gN_cache; int /*<<< orphan*/ * users_pwd; int /*<<< orphan*/ * seed_key; int /*<<< orphan*/ * default_N; int /*<<< orphan*/ * default_g; } ;
typedef  TYPE_1__ SRP_VBASE ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char*) ; 
 int /*<<< orphan*/  sk_SRP_gN_cache_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_SRP_gN_cache_new_null () ; 
 int /*<<< orphan*/  sk_SRP_user_pwd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_SRP_user_pwd_new_null () ; 

SRP_VBASE *SRP_VBASE_new(char *seed_key)
{
    SRP_VBASE *vb = OPENSSL_malloc(sizeof(*vb));

    if (vb == NULL)
        return NULL;
    if ((vb->users_pwd = sk_SRP_user_pwd_new_null()) == NULL
        || (vb->gN_cache = sk_SRP_gN_cache_new_null()) == NULL) {
        OPENSSL_free(vb);
        return NULL;
    }
    vb->default_g = NULL;
    vb->default_N = NULL;
    vb->seed_key = NULL;
    if ((seed_key != NULL) && (vb->seed_key = OPENSSL_strdup(seed_key)) == NULL) {
        sk_SRP_user_pwd_free(vb->users_pwd);
        sk_SRP_gN_cache_free(vb->gN_cache);
        OPENSSL_free(vb);
        return NULL;
    }
    return vb;
}