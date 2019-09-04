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
struct TYPE_6__ {int /*<<< orphan*/ * result_session_ticket_app_data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * expected_session_ticket_app_data; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;
typedef  TYPE_2__ HANDSHAKE_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_str_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_session_ticket_app_data(HANDSHAKE_RESULT *result,
                                         SSL_TEST_CTX *test_ctx)
{
    size_t result_len = 0;
    size_t expected_len = 0;

    /* consider empty and NULL strings to be the same */
    if (result->result_session_ticket_app_data != NULL)
        result_len = strlen(result->result_session_ticket_app_data);
    if (test_ctx->expected_session_ticket_app_data != NULL)
        expected_len = strlen(test_ctx->expected_session_ticket_app_data);
    if (result_len == 0 && expected_len == 0)
        return 1;

    if (!TEST_str_eq(result->result_session_ticket_app_data,
                     test_ctx->expected_session_ticket_app_data))
        return 0;

    return 1;
}