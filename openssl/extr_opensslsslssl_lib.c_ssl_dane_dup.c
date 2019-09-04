#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  dlen; int /*<<< orphan*/  data; int /*<<< orphan*/  mtype; int /*<<< orphan*/  selector; int /*<<< orphan*/  usage; } ;
typedef  TYPE_2__ danetls_record ;
struct TYPE_13__ {int /*<<< orphan*/ * trecs; int /*<<< orphan*/ * dctx; int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {TYPE_7__ dane; TYPE_1__* ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  dane; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  DANETLS_ENABLED (TYPE_7__*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  SSL_F_SSL_DANE_DUP ; 
 scalar_t__ SSL_dane_tlsa_add (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dane_final (TYPE_7__*) ; 
 int /*<<< orphan*/ * sk_danetls_record_new_reserve (int /*<<< orphan*/ *,int) ; 
 int sk_danetls_record_num (int /*<<< orphan*/ *) ; 
 TYPE_2__* sk_danetls_record_value (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ssl_dane_dup(SSL *to, SSL *from)
{
    int num;
    int i;

    if (!DANETLS_ENABLED(&from->dane))
        return 1;

    num = sk_danetls_record_num(from->dane.trecs);
    dane_final(&to->dane);
    to->dane.flags = from->dane.flags;
    to->dane.dctx = &to->ctx->dane;
    to->dane.trecs = sk_danetls_record_new_reserve(NULL, num);

    if (to->dane.trecs == NULL) {
        SSLerr(SSL_F_SSL_DANE_DUP, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    for (i = 0; i < num; ++i) {
        danetls_record *t = sk_danetls_record_value(from->dane.trecs, i);

        if (SSL_dane_tlsa_add(to, t->usage, t->selector, t->mtype,
                              t->data, t->dlen) <= 0)
            return 0;
    }
    return 1;
}