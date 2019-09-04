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
struct TYPE_6__ {int /*<<< orphan*/  cipher; } ;
struct TYPE_5__ {int /*<<< orphan*/ * expected_cipher; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;
typedef  TYPE_2__ HANDSHAKE_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_str_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_cipher(HANDSHAKE_RESULT *result, SSL_TEST_CTX *test_ctx)
{
    if (test_ctx->expected_cipher == NULL)
        return 1;
    if (!TEST_ptr(result->cipher))
        return 0;
    if (!TEST_str_eq(test_ctx->expected_cipher,
                     result->cipher))
        return 0;
    return 1;
}