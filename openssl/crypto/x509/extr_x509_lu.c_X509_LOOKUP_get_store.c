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
typedef  int /*<<< orphan*/  X509_STORE ;
struct TYPE_3__ {int /*<<< orphan*/ * store_ctx; } ;
typedef  TYPE_1__ X509_LOOKUP ;

/* Variables and functions */

X509_STORE *X509_LOOKUP_get_store(const X509_LOOKUP *ctx)
{
    return ctx->store_ctx;
}