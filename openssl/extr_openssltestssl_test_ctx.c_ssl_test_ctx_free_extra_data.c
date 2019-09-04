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
struct TYPE_3__ {int /*<<< orphan*/  resume_extra; int /*<<< orphan*/  extra; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ssl_test_extra_conf_free_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ssl_test_ctx_free_extra_data(SSL_TEST_CTX *ctx)
{
    ssl_test_extra_conf_free_data(&ctx->extra);
    ssl_test_extra_conf_free_data(&ctx->resume_extra);
}