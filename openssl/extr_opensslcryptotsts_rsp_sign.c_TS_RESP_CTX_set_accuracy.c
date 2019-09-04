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
struct TYPE_4__ {int /*<<< orphan*/ * micros; int /*<<< orphan*/ * millis; int /*<<< orphan*/ * seconds; } ;
typedef  TYPE_1__ TS_RESP_CTX ;

/* Variables and functions */
 void* ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  TS_F_TS_RESP_CTX_SET_ACCURACY ; 
 int /*<<< orphan*/  TS_RESP_CTX_accuracy_free (TYPE_1__*) ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TS_RESP_CTX_set_accuracy(TS_RESP_CTX *ctx,
                             int secs, int millis, int micros)
{

    TS_RESP_CTX_accuracy_free(ctx);
    if (secs
        && ((ctx->seconds = ASN1_INTEGER_new()) == NULL
            || !ASN1_INTEGER_set(ctx->seconds, secs)))
        goto err;
    if (millis
        && ((ctx->millis = ASN1_INTEGER_new()) == NULL
            || !ASN1_INTEGER_set(ctx->millis, millis)))
        goto err;
    if (micros
        && ((ctx->micros = ASN1_INTEGER_new()) == NULL
            || !ASN1_INTEGER_set(ctx->micros, micros)))
        goto err;

    return 1;
 err:
    TS_RESP_CTX_accuracy_free(ctx);
    TSerr(TS_F_TS_RESP_CTX_SET_ACCURACY, ERR_R_MALLOC_FAILURE);
    return 0;
}