#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* method; } ;
typedef  TYPE_2__ X509_LOOKUP ;
struct TYPE_5__ {int (* init ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*) ; 

int X509_LOOKUP_init(X509_LOOKUP *ctx)
{
    if (ctx->method == NULL)
        return 0;
    if (ctx->method->init != NULL)
        return ctx->method->init(ctx);
    else
        return 1;
}