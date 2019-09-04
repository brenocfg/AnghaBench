#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  g; int /*<<< orphan*/  N; } ;
struct TYPE_6__ {int /*<<< orphan*/ * v; int /*<<< orphan*/ * s; void* g; void* N; } ;
struct TYPE_7__ {TYPE_1__ srp_ctx; } ;
typedef  TYPE_2__ SSL ;
typedef  TYPE_3__ SRP_gN ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 void* BN_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_create_verifier_BN (char const*,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* SRP_get_default_gN (char const*) ; 

int SSL_set_srp_server_param_pw(SSL *s, const char *user, const char *pass,
                                const char *grp)
{
    SRP_gN *GN = SRP_get_default_gN(grp);
    if (GN == NULL)
        return -1;
    s->srp_ctx.N = BN_dup(GN->N);
    s->srp_ctx.g = BN_dup(GN->g);
    BN_clear_free(s->srp_ctx.v);
    s->srp_ctx.v = NULL;
    BN_clear_free(s->srp_ctx.s);
    s->srp_ctx.s = NULL;
    if (!SRP_create_verifier_BN
        (user, pass, &s->srp_ctx.s, &s->srp_ctx.v, GN->N, GN->g))
        return -1;

    return 1;
}