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
struct TYPE_6__ {int /*<<< orphan*/  servername; } ;
struct TYPE_5__ {int /*<<< orphan*/  expected_servername; } ;
typedef  TYPE_1__ SSL_TEST_CTX ;
typedef  TYPE_2__ HANDSHAKE_RESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_servername_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_servername(HANDSHAKE_RESULT *result, SSL_TEST_CTX *test_ctx)
{
    if (!TEST_int_eq(result->servername, test_ctx->expected_servername)) {
      TEST_info("Client ServerName mismatch, expected %s, got %s.",
                ssl_servername_name(test_ctx->expected_servername),
                ssl_servername_name(result->servername));
      return 0;
    }
  return 1;
}