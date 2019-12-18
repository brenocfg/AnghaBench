#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_get_max_proto_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_get_min_proto_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  ctx ; 

__attribute__((used)) static int test_func(void)
{
    if (!TEST_int_eq(SSL_CTX_get_min_proto_version(ctx), TLS1_2_VERSION)
        && !TEST_int_eq(SSL_CTX_get_max_proto_version(ctx), TLS1_2_VERSION)) {
        TEST_info("min/max version setting incorrect");
        return 0;
    }
    return 1;
}