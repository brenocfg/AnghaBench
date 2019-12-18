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
typedef  int /*<<< orphan*/  X509_STORE_CTX_check_revocation_fn ;
struct TYPE_3__ {int /*<<< orphan*/  check_revocation; } ;
typedef  TYPE_1__ X509_STORE ;

/* Variables and functions */

void X509_STORE_set_check_revocation(X509_STORE *ctx,
                                     X509_STORE_CTX_check_revocation_fn check_revocation)
{
    ctx->check_revocation = check_revocation;
}