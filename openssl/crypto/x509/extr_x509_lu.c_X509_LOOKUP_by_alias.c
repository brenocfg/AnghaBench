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
typedef  int /*<<< orphan*/  X509_OBJECT ;
typedef  int /*<<< orphan*/  X509_LOOKUP_TYPE ;
struct TYPE_6__ {TYPE_1__* method; } ;
typedef  TYPE_2__ X509_LOOKUP ;
struct TYPE_5__ {int (* get_by_alias ) (TYPE_2__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 

int X509_LOOKUP_by_alias(X509_LOOKUP *ctx, X509_LOOKUP_TYPE type,
                         const char *str, int len, X509_OBJECT *ret)
{
    if ((ctx->method == NULL) || (ctx->method->get_by_alias == NULL))
        return 0;
    return ctx->method->get_by_alias(ctx, type, str, len, ret);
}