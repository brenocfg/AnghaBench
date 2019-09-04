#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  v; int /*<<< orphan*/  s; int /*<<< orphan*/  info; int /*<<< orphan*/  id; int /*<<< orphan*/  N; int /*<<< orphan*/  g; } ;
typedef  TYPE_1__ SRP_user_pwd ;

/* Variables and functions */
 int /*<<< orphan*/  BN_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_user_pwd_free (TYPE_1__*) ; 
 TYPE_1__* SRP_user_pwd_new () ; 
 int /*<<< orphan*/  SRP_user_pwd_set0_sv (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_user_pwd_set1_ids (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_user_pwd_set_gN (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRP_user_pwd *srp_user_pwd_dup(SRP_user_pwd *src)
{
    SRP_user_pwd *ret;

    if (src == NULL)
        return NULL;
    if ((ret = SRP_user_pwd_new()) == NULL)
        return NULL;

    SRP_user_pwd_set_gN(ret, src->g, src->N);
    if (!SRP_user_pwd_set1_ids(ret, src->id, src->info)
        || !SRP_user_pwd_set0_sv(ret, BN_dup(src->s), BN_dup(src->v))) {
            SRP_user_pwd_free(ret);
            return NULL;
    }
    return ret;
}