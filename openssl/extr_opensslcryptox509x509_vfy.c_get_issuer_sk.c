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
struct TYPE_4__ {int /*<<< orphan*/  other_ctx; } ;
typedef  TYPE_1__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  X509_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_issuer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_issuer_sk(X509 **issuer, X509_STORE_CTX *ctx, X509 *x)
{
    *issuer = find_issuer(ctx, ctx->other_ctx, x);
    if (*issuer) {
        X509_up_ref(*issuer);
        return 1;
    } else
        return 0;
}