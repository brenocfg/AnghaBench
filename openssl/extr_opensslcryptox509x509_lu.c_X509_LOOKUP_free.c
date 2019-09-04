#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* method; } ;
typedef  TYPE_2__ X509_LOOKUP ;
struct TYPE_6__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void X509_LOOKUP_free(X509_LOOKUP *ctx)
{
    if (ctx == NULL)
        return;
    if ((ctx->method != NULL) && (ctx->method->free != NULL))
        (*ctx->method->free) (ctx);
    OPENSSL_free(ctx);
}