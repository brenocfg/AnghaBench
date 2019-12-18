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
struct TYPE_2__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  cipher; } ;
struct test_tls_crypt_context {TYPE_1__ kt; } ;

/* Variables and functions */
 int /*<<< orphan*/  skip () ; 

__attribute__((used)) static void skip_if_tls_crypt_not_supported(struct test_tls_crypt_context *ctx)
{
    if (!ctx->kt.cipher || !ctx->kt.digest)
    {
        skip();
    }
}