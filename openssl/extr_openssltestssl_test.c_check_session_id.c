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
struct TYPE_6__ {scalar_t__ session_id; } ;
struct TYPE_5__ {scalar_t__ session_id_expected; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;
typedef  TYPE_2__ HANDSHAKE_RESULT ;

/* Variables and functions */
 scalar_t__ SSL_TEST_SESSION_ID_IGNORE ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ssl_session_id_name (scalar_t__) ; 

__attribute__((used)) static int check_session_id(HANDSHAKE_RESULT *result, SSL_TEST_CTX *test_ctx)
{
    if (test_ctx->session_id_expected == SSL_TEST_SESSION_ID_IGNORE)
        return 1;
    if (!TEST_int_eq(result->session_id, test_ctx->session_id_expected)) {
        TEST_info("Client SessionIdExpected mismatch, expected %s, got %s\n.",
                ssl_session_id_name(test_ctx->session_id_expected),
                ssl_session_id_name(result->session_id));
        return 0;
    }
    return 1;
}