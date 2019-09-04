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
struct TYPE_2__ {int /*<<< orphan*/  strength; int /*<<< orphan*/  v; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  A; int /*<<< orphan*/  B; int /*<<< orphan*/  s; int /*<<< orphan*/  g; int /*<<< orphan*/  N; int /*<<< orphan*/  info; int /*<<< orphan*/  login; } ;
struct ssl_st {TYPE_1__ srp_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_MINIMAL_N ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int SSL_SRP_CTX_free(struct ssl_st *s)
{
    if (s == NULL)
        return 0;
    OPENSSL_free(s->srp_ctx.login);
    OPENSSL_free(s->srp_ctx.info);
    BN_free(s->srp_ctx.N);
    BN_free(s->srp_ctx.g);
    BN_free(s->srp_ctx.s);
    BN_free(s->srp_ctx.B);
    BN_free(s->srp_ctx.A);
    BN_free(s->srp_ctx.a);
    BN_free(s->srp_ctx.b);
    BN_free(s->srp_ctx.v);
    memset(&s->srp_ctx, 0, sizeof(s->srp_ctx));
    s->srp_ctx.strength = SRP_MINIMAL_N;
    return 1;
}