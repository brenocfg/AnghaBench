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
struct TYPE_3__ {int /*<<< orphan*/ * v; int /*<<< orphan*/ * s; } ;
typedef  TYPE_1__ SRP_user_pwd ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 

int SRP_user_pwd_set0_sv(SRP_user_pwd *vinfo, BIGNUM *s, BIGNUM *v)
{
    BN_free(vinfo->s);
    BN_clear_free(vinfo->v);
    vinfo->v = v;
    vinfo->s = s;
    return (vinfo->s != NULL && vinfo->v != NULL);
}